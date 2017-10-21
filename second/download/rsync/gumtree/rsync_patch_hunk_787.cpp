    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
 #include "rsync.h"
 
 extern int verbose;
-extern int recurse;
-extern int delete_after;
-extern int max_delete;
-extern int csum_length;
-extern struct stats stats;
 extern int dry_run;
+extern int am_daemon;
+extern int am_server;
+extern int do_progress;
+extern int log_before_transfer;
+extern int log_format_has_i;
+extern int daemon_log_format_has_i;
+extern int csum_length;
 extern int read_batch;
 extern int batch_gen_fd;
-extern int am_server;
+extern int protocol_version;
 extern int relative_paths;
 extern int keep_dirlinks;
 extern int preserve_hard_links;
 extern int preserve_perms;
-extern int cvs_exclude;
 extern int io_error;
-extern char *tmpdir;
-extern char *partial_dir;
-extern char *compare_dest;
+extern int basis_dir_cnt;
 extern int make_backups;
-extern int do_progress;
-extern char *backup_dir;
-extern char *backup_suffix;
-extern int backup_suffix_len;
 extern int cleanup_got_literal;
+extern int remove_sent_files;
 extern int module_id;
 extern int ignore_errors;
 extern int orig_umask;
 extern int keep_partial;
 extern int checksum_seed;
 extern int inplace;
+extern int delay_updates;
+extern struct stats stats;
+extern char *log_format;
+extern char *tmpdir;
+extern char *partial_dir;
+extern char *basis_dir[];
+extern struct file_list *the_file_list;
+extern struct filter_list_struct server_filter_list;
+
+#define SLOT_SIZE	(16*1024)	/* Desired size in bytes */
+#define PER_SLOT_BITS	(SLOT_SIZE * 8) /* Number of bits per slot */
+#define PER_SLOT_INTS	(SLOT_SIZE / 4) /* Number of int32s per slot */
+
+static uint32 **delayed_bits = NULL;
+static int delayed_slot_cnt = 0;
+static int phase = 0;
 
-extern struct exclude_list_struct server_exclude_list;
-
-
-static void delete_one(char *fn, int is_dir)
+static void init_delayed_bits(int max_ndx)
 {
-	if (!is_dir) {
-		if (robust_unlink(fn) != 0) {
-			rsyserr(FERROR, errno, "delete_one: unlink %s failed",
-				full_fname(fn));
-		} else if (verbose)
-			rprintf(FINFO, "deleting %s\n", safe_fname(fn));
-	} else {
-		if (do_rmdir(fn) != 0) {
-			if (errno != ENOTEMPTY && errno != EEXIST) {
-				rsyserr(FERROR, errno,
-					"delete_one: rmdir %s failed",
-					full_fname(fn));
-			}
-		} else if (verbose) {
-			rprintf(FINFO, "deleting directory %s\n",
-				safe_fname(fn));
-		}
-	}
-}
-
+	delayed_slot_cnt = (max_ndx + PER_SLOT_BITS - 1) / PER_SLOT_BITS;
 
-static int is_backup_file(char *fn)
-{
-	int k = strlen(fn) - backup_suffix_len;
-	return k > 0 && strcmp(fn+k, backup_suffix) == 0;
+	if (!(delayed_bits = (uint32**)calloc(delayed_slot_cnt, sizeof (uint32*))))
+		out_of_memory("set_delayed_bit");
 }
 
-
-/* This deletes any files on the receiving side that are not present
- * on the sending side. */
-void delete_files(struct file_list *flist)
+static void set_delayed_bit(int ndx)
 {
-	struct file_list *local_file_list;
-	int i, j;
-	char *argv[1], fbuf[MAXPATHLEN];
-	static int deletion_count;
-
-	if (cvs_exclude)
-		add_cvs_excludes();
-
-	if (io_error && !(lp_ignore_errors(module_id) || ignore_errors)) {
-		rprintf(FINFO,"IO error encountered - skipping file deletion\n");
-		return;
-	}
+	int slot = ndx / PER_SLOT_BITS;
+	ndx %= PER_SLOT_BITS;
 
-	for (j = 0; j < flist->count; j++) {
-		if (!(flist->files[j]->flags & FLAG_TOP_DIR)
-		    || !S_ISDIR(flist->files[j]->mode))
-			continue;
+	if (!delayed_bits[slot]) {
+		if (!(delayed_bits[slot] = (uint32*)calloc(PER_SLOT_INTS, 4)))
+			out_of_memory("set_delayed_bit");
+	}
 
-		argv[0] = f_name_to(flist->files[j], fbuf);
+	delayed_bits[slot][ndx/32] |= 1u << (ndx % 32);
+}
 
-		if (!(local_file_list = send_file_list(-1, 1, argv)))
+/* Call this with -1 to start checking from 0.  Returns -1 at the end. */
+static int next_delayed_bit(int after)
+{
+	uint32 bits, mask;
+	int i, ndx = after + 1;
+	int slot = ndx / PER_SLOT_BITS;
+	ndx %= PER_SLOT_BITS;
+
+	mask = (1u << (ndx % 32)) - 1;
+	for (i = ndx / 32; slot < delayed_slot_cnt; slot++, i = mask = 0) {
+		if (!delayed_bits[slot])
 			continue;
-
-		if (verbose > 1)
-			rprintf(FINFO, "deleting in %s\n", safe_fname(fbuf));
-
-		for (i = local_file_list->count-1; i >= 0; i--) {
-			if (max_delete && deletion_count > max_delete)
-				break;
-			if (!local_file_list->files[i]->basename)
+		for ( ; i < PER_SLOT_INTS; i++, mask = 0) {
+			if (!(bits = delayed_bits[slot][i] & ~mask))
 				continue;
-			if (flist_find(flist,local_file_list->files[i]) < 0) {
-				char *f = f_name(local_file_list->files[i]);
-				if (make_backups && (backup_dir || !is_backup_file(f))) {
-					make_backup(f);
-					if (verbose) {
-						rprintf(FINFO, "deleting %s\n",
-							safe_fname(f));
-					}
-				} else {
-					int mode = local_file_list->files[i]->mode;
-					delete_one(f, S_ISDIR(mode) != 0);
-				}
-				deletion_count++;
+			/* The xor magic figures out the lowest enabled bit in
+			 * bits, and the switch quickly computes log2(bit). */
+			switch (bits ^ (bits & (bits-1))) {
+#define LOG2(n) case 1u << n: return slot*PER_SLOT_BITS + i*32 + n
+			    LOG2(0);  LOG2(1);  LOG2(2);  LOG2(3);
+			    LOG2(4);  LOG2(5);  LOG2(6);  LOG2(7);
+			    LOG2(8);  LOG2(9);  LOG2(10); LOG2(11);
+			    LOG2(12); LOG2(13); LOG2(14); LOG2(15);
+			    LOG2(16); LOG2(17); LOG2(18); LOG2(19);
+			    LOG2(20); LOG2(21); LOG2(22); LOG2(23);
+			    LOG2(24); LOG2(25); LOG2(26); LOG2(27);
+			    LOG2(28); LOG2(29); LOG2(30); LOG2(31);
 			}
+			return -1; /* impossible... */
 		}
-		flist_free(local_file_list);
 	}
+
+	return -1;
 }
 
 
 /*
  * get_tmpname() - create a tmp filename for a given filename
  *
