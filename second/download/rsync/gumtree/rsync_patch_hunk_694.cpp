 /* -*- c-file-style: "linux" -*-
-   
+
    Weiss 1/1999
    Batch utilities for rsync.
 
 */
 
 #include "rsync.h"
 #include <time.h>
 
 extern char *batch_prefix;
+extern int csum_length;
+extern int protocol_version;
+extern struct stats stats;
 
 struct file_list *batch_flist;
 
 static char rsync_flist_file[] = ".rsync_flist";
 static char rsync_csums_file[] = ".rsync_csums";
 static char rsync_delta_file[] = ".rsync_delta";
 static char rsync_argvs_file[] = ".rsync_argvs";
 
-static int fdb;
-static int fdb_delta;
-static int fdb_open;
-static int fdb_close;
+static int f_csums = -1;
+static int f_delta = -1;
 
-void write_batch_flist_file(char *buff, int bytes_to_write)
+void write_batch_flist_info(int flist_count, struct file_struct **files)
 {
 	char filename[MAXPATHLEN];
+	int i, f, save_pv;
+	int64 save_written;
 
-	if (fdb_open) {
-		/* Set up file extension */
-		strlcpy(filename, batch_prefix, sizeof(filename));
-		strlcat(filename, rsync_flist_file, sizeof(filename));
+	stringjoin(filename, sizeof filename,
+	    batch_prefix, rsync_flist_file, NULL);
 
-		/*
-		 * Open batch flist file for writing;
-		 * create it if it doesn't exist
-		 */
-		fdb = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
-			    S_IREAD | S_IWRITE);
-		if (fdb == -1) {
-			rprintf(FERROR, "Batch file %s open error: %s\n",
-				filename, strerror(errno));
-			close(fdb);
-			exit_cleanup(1);
-		}
-		fdb_open = 0;
-	}
-
-	/* Write buffer to batch flist file */
-
-	if (write(fdb, buff, bytes_to_write) == -1) {
-		rprintf(FERROR, "Batch file %s write error: %s\n",
-			filename, strerror(errno));
-		close(fdb);
+	f = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
+	if (f < 0) {
+		rprintf(FERROR, "Batch file %s open error: %s\n",
+		    filename, strerror(errno));
 		exit_cleanup(1);
 	}
 
-	if (fdb_close) {
-		close(fdb);
-	}
-}
-
-void write_batch_flist_info(int flist_count, struct file_struct **fptr)
-{
-	int i;
-	int bytes_to_write;
-
-	/* Write flist info to batch file */
-
-	bytes_to_write =
-	    sizeof(unsigned) +
-	    sizeof(time_t) +
-	    sizeof(OFF_T) +
-	    sizeof(mode_t) +
-	    sizeof(INO64_T) +
-	    sizeof(DEV64_T) +
-	    sizeof(DEV64_T) +
-	    sizeof(uid_t) +
-	    sizeof(gid_t);
-
-	fdb_open = 1;
-	fdb_close = 0;
+	save_written = stats.total_written;
+	save_pv = protocol_version;
+	protocol_version = PROTOCOL_VERSION;
+	write_int(f, protocol_version);
+	write_int(f, flist_count);
 
 	for (i = 0; i < flist_count; i++) {
-		write_batch_flist_file((char *) fptr[i], bytes_to_write);
-		write_char_bufs(fptr[i]->basename);
-		write_char_bufs(fptr[i]->dirname);
-		write_char_bufs(fptr[i]->basedir);
-		write_char_bufs(fptr[i]->link);
-		if (i == flist_count - 1) {
-			fdb_close = 1;
-		}
-		write_char_bufs(fptr[i]->sum);
+		send_file_entry(files[i], f,
+		    files[i]->flags & FLAG_TOP_DIR ?  XMIT_TOP_DIR : 0);
 	}
-}
+	send_file_entry(NULL, f, 0);
 
-void write_char_bufs(char *buf)
-{
-	/* Write the size of the string which will follow  */
-
-	char b[4];
-
-	SIVAL(b, 0, buf != NULL ? strlen(buf) : 0);
-
-	write_batch_flist_file(b, sizeof(int));
+	protocol_version = save_pv;
+	stats.total_written = save_written;
 
-	/*  Write the string if there is one */
-
-	if (buf != NULL) {
-		write_batch_flist_file(buf, strlen(buf));
-	}
+	close(f);
 }
 
+
 void write_batch_argvs_file(int argc, char *argv[])
 {
-	int fdb;
+	int f;
 	int i;
 	char buff[256]; /* XXX */
 	char buff2[MAXPATHLEN + 6];
 	char filename[MAXPATHLEN];
 
-	/* Set up file extension */
-	strlcpy(filename, batch_prefix, sizeof(filename));
-	strlcat(filename, rsync_argvs_file, sizeof(filename));
-
-	/*
-	 * Open batch argvs file for writing;
-	 * create it if it doesn't exist
-	 */
-	fdb = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
-		      S_IREAD | S_IWRITE | S_IEXEC);
-	if (fdb == -1) {
+	stringjoin(filename, sizeof filename,
+	    batch_prefix, rsync_argvs_file, NULL);
+
+	f = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
+	    S_IRUSR | S_IWUSR | S_IEXEC);
+	if (f < 0) {
 		rprintf(FERROR, "Batch file %s open error: %s\n",
-			filename, strerror(errno));
-		close(fdb);
+		    filename, strerror(errno));
 		exit_cleanup(1);
 	}
 	buff[0] = '\0';
 
 	/* Write argvs info to batch file */
 
 	for (i = 0; i < argc; ++i) {
 		if (i == argc - 2) /* Skip source directory on cmdline */
-		    continue;
+			continue;
 		/*
 		 * FIXME:
 		 * I think directly manipulating argv[] is probably bogus
 		 */
 		if (!strncmp(argv[i], "--write-batch",
-			strlen("--write-batch"))) {
+		    strlen("--write-batch"))) {
 			/* Safer to change it here than script */
 			/*
 			 * Change to --read-batch=prefix
 			 * to get ready for remote
 			 */
-			strlcat(buff, "--read-batch=", sizeof(buff));
-			strlcat(buff, batch_prefix, sizeof(buff));
+			strlcat(buff, "--read-batch=", sizeof buff);
+			strlcat(buff, batch_prefix, sizeof buff);
 		} else
 		if (i == argc - 1) {
-		    snprintf(buff2, sizeof(buff2), "${1:-%s}", argv[i]);
-		    strlcat(buff, buff2, sizeof(buff));
+			snprintf(buff2, sizeof buff2, "${1:-%s}", argv[i]);
+			strlcat(buff, buff2, sizeof buff);
 		}
 		else {
-			strlcat(buff, argv[i], sizeof(buff));
+			strlcat(buff, argv[i], sizeof buff);
 		}
 
 		if (i < (argc - 1)) {
-			strlcat(buff, " ", sizeof(buff));
+			strlcat(buff, " ", sizeof buff);
 		}
 	}
-	strlcat(buff, "\n", sizeof(buff));
-	if (!write(fdb, buff, strlen(buff))) {
+	strlcat(buff, "\n", sizeof buff);
+	if (!write(f, buff, strlen(buff))) {
 		rprintf(FERROR, "Batch file %s write error: %s\n",
-			filename, strerror(errno));
-		close(fdb);
+		    filename, strerror(errno));
+		close(f);
 		exit_cleanup(1);
 	}
-	close(fdb);
+	close(f);
 }
 
 struct file_list *create_flist_from_batch(void)
 {
-	unsigned char flags;
-
-	fdb_open = 1;
-	fdb_close = 0;
-
-	batch_flist = new(struct file_list);
-	if (!batch_flist) {
-		out_of_memory("create_flist_from_batch");
-	}
-	batch_flist->count = 0;
-	batch_flist->malloced = 1000;
-	batch_flist->files = new_array(struct file_struct *,
-				       batch_flist->malloced);
-	if (!batch_flist->files) {
-		out_of_memory("create_flist_from_batch");
-	}
-
-	for (flags = read_batch_flags(); flags; flags = read_batch_flags()) {
-
-		int i = batch_flist->count;
-
-		if (i >= batch_flist->malloced) {
-			if (batch_flist->malloced < 1000)
-				batch_flist->malloced += 1000;
-			else
-				batch_flist->malloced *= 2;
-			batch_flist->files
-				= realloc_array(batch_flist->files,
-						struct file_struct *,
-						batch_flist->malloced);
-			if (!batch_flist->files)
-				out_of_memory("create_flist_from_batch");
-		}
-		read_batch_flist_info(&batch_flist->files[i]);
-		batch_flist->files[i]->flags = flags;
-
-		batch_flist->count++;
-	}
-
-	return batch_flist;
-}
-
-int read_batch_flist_file(char *buff, int len)
-{
-	int bytes_read;
 	char filename[MAXPATHLEN];
+	unsigned short flags;
+	int i, f, save_pv;
+	int64 save_read;
 
-	if (fdb_open) {
-		/* Set up file extension */
-		strlcpy(filename, batch_prefix, sizeof(filename));
-		strlcat(filename, rsync_flist_file, sizeof(filename));
-
-		/* Open batch flist file for reading */
-		fdb = do_open(filename, O_RDONLY, 0);
-		if (fdb == -1) {
-			rprintf(FERROR, "Batch file %s open error: %s\n",
-				filename, strerror(errno));
-			close(fdb);
-			exit_cleanup(1);
-		}
-		fdb_open = 0;
-	}
-
-	/* Read flist batch file */
+	stringjoin(filename, sizeof filename,
+	    batch_prefix, rsync_flist_file, NULL);
 
-	switch (bytes_read = read(fdb, buff, len)) {
-	    case -1:
-		rprintf(FERROR, "Batch file %s read error: %s\n",
-			filename, strerror(errno));
-		close(fdb);
+	f = do_open(filename, O_RDONLY, 0);
+	if (f < 0) {
+		rprintf(FERROR, "Batch file %s open error: %s\n",
+		    filename, strerror(errno));
 		exit_cleanup(1);
-		break;
-	    case 0:	/* EOF */
-		close(fdb);
 	}
 
-	return bytes_read;
-}
-
-unsigned char read_batch_flags(void)
-{
-	int flags;
-
-	if (read_batch_flist_file((char *) &flags, 4)) {
-		return 1;
-	} else {
-		return 0;
-	}
-}
+	batch_flist = flist_new(WITH_HLINK, "create_flist_from_batch");
 
-void read_batch_flist_info(struct file_struct **fptr)
-{
-	int int_str_len;
-	char char_str_len[4];
-	char buff[256];
-	struct file_struct *file;
-
-	file = new(struct file_struct);
-	if (!file)
-		out_of_memory("read_batch_flist_info");
-	memset((char *) file, 0, sizeof(*file));
-
-	*fptr = file;
-
-	/*
-	 * Keep these in sync with bytes_to_write assignment
-	 * in write_batch_flist_info()
-	 */
-	read_batch_flist_file((char *) &file->modtime, sizeof(time_t));
-	read_batch_flist_file((char *) &file->length, sizeof(OFF_T));
-	read_batch_flist_file((char *) &file->mode, sizeof(mode_t));
-	read_batch_flist_file((char *) &file->inode, sizeof(INO64_T));
-	read_batch_flist_file((char *) &file->dev, sizeof(DEV64_T));
-	read_batch_flist_file((char *) &file->rdev, sizeof(DEV64_T));
-	read_batch_flist_file((char *) &file->uid, sizeof(uid_t));
-	read_batch_flist_file((char *) &file->gid, sizeof(gid_t));
-	read_batch_flist_file(char_str_len, sizeof(char_str_len));
-	int_str_len = IVAL(char_str_len, 0);
-	if (int_str_len > 0) {
-		read_batch_flist_file(buff, int_str_len);
-		buff[int_str_len] = '\0';
-		file->basename = strdup(buff);
-	} else {
-		file->basename = NULL;
-	}
+	save_read = stats.total_read;
+	save_pv = protocol_version;
+	protocol_version = read_int(f);
 
-	read_batch_flist_file(char_str_len, sizeof(char_str_len));
-	int_str_len = IVAL(char_str_len, 0);
-	if (int_str_len > 0) {
-		read_batch_flist_file(buff, int_str_len);
-		buff[int_str_len] = '\0';
-		file[0].dirname = strdup(buff);
-	} else {
-		file[0].dirname = NULL;
-	}
+	batch_flist->count = read_int(f);
+	flist_expand(batch_flist);
 
-	read_batch_flist_file(char_str_len, sizeof(char_str_len));
-	int_str_len = IVAL(char_str_len, 0);
-	if (int_str_len > 0) {
-		read_batch_flist_file(buff, int_str_len);
-		buff[int_str_len] = '\0';
-		file[0].basedir = strdup(buff);
-	} else {
-		file[0].basedir = NULL;
+	for (i = 0; (flags = read_byte(f)) != 0; i++) {
+		if (protocol_version >= 28 && (flags & XMIT_EXTENDED_FLAGS))
+			flags |= read_byte(f) << 8;
+		receive_file_entry(&batch_flist->files[i], flags, batch_flist, f);
 	}
+	receive_file_entry(NULL, 0, NULL, 0); /* Signal that we're done. */
 
-	read_batch_flist_file(char_str_len, sizeof(char_str_len));
-	int_str_len = IVAL(char_str_len, 0);
-	if (int_str_len > 0) {
-		read_batch_flist_file(buff, int_str_len);
-		buff[int_str_len] = '\0';
-		file[0].link = strdup(buff);
-	} else {
-		file[0].link = NULL;
-	}
+	protocol_version = save_pv;
+	stats.total_read = save_read;
 
-	read_batch_flist_file(char_str_len, sizeof(char_str_len));
-	int_str_len = IVAL(char_str_len, 0);
-	if (int_str_len > 0) {
-		read_batch_flist_file(buff, int_str_len);
-		buff[int_str_len] = '\0';
-		file[0].sum = strdup(buff);
-	} else {
-		file[0].sum = NULL;
-	}
+	return batch_flist;
 }
 
 void write_batch_csums_file(void *buff, int bytes_to_write)
 {
-	static int fdb_open = 1;
-	char filename[MAXPATHLEN];
-
-	if (fdb_open) {
-		/* Set up file extension */
-		strlcpy(filename, batch_prefix, sizeof(filename));
-		strlcat(filename, rsync_csums_file, sizeof(filename));
-
-		/*
-		 * Open batch csums file for writing;
-		 * create it if it doesn't exist
-		 */
-		fdb = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
-			    S_IREAD | S_IWRITE);
-		if (fdb == -1) {
-			rprintf(FERROR, "Batch file %s open error: %s\n",
-				filename, strerror(errno));
-			close(fdb);
-			exit_cleanup(1);
-		}
-		fdb_open = 0;
-	}
-
-	/* Write buffer to batch csums file */
-
-	if (write(fdb, buff, bytes_to_write) == -1) {
-		rprintf(FERROR, "Batch file %s write error: %s\n",
-			filename, strerror(errno));
-		close(fdb);
+	if (write(f_csums, buff, bytes_to_write) < 0) {
+		rprintf(FERROR, "Batch file write error: %s\n",
+		    strerror(errno));
+		close(f_csums);
 		exit_cleanup(1);
 	}
 }
 
 void close_batch_csums_file(void)
 {
-	close(fdb);
+	close(f_csums);
+	f_csums = -1;
 }
 
 
 /**
- * Write csum info to batch file 
+ * Write csum info to batch file
  *
  * @todo This will break if s->count is ever larger than maxint.  The
  * batch code should probably be changed to consistently use the
  * variable-length integer routines, which is probably a compatible
  * change.
  **/
-void write_batch_csum_info(int *flist_entry, int flist_count,
-			   struct sum_struct *s)
+void write_batch_csum_info(int *flist_entry, struct sum_struct *s)
 {
 	size_t i;
 	int int_count;
-	extern int csum_length;
+	char filename[MAXPATHLEN];
 
-	fdb_open = 1;
+	if (f_csums < 0) {
+		stringjoin(filename, sizeof filename,
+		    batch_prefix, rsync_csums_file, NULL);
+
+		f_csums = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
+		    S_IRUSR | S_IWUSR);
+		if (f_csums < 0) {
+			rprintf(FERROR, "Batch file %s open error: %s\n",
+			    filename, strerror(errno));
+			close(f_csums);
+			exit_cleanup(1);
+		}
+	}
 
-	write_batch_csums_file(flist_entry, sizeof(int));
+	write_batch_csums_file(flist_entry, sizeof (int));
 	int_count = s ? (int) s->count : 0;
 	write_batch_csums_file(&int_count, sizeof int_count);
-	
+
 	if (s) {
 		for (i = 0; i < s->count; i++) {
-			write_batch_csums_file(&s->sums[i].sum1, sizeof(uint32));
-			if ((*flist_entry == flist_count - 1)
-			    && (i == s->count - 1)) {
-				fdb_close = 1;
-			}
+			write_batch_csums_file(&s->sums[i].sum1,
+			    sizeof (uint32));
 			write_batch_csums_file(s->sums[i].sum2, csum_length);
 		}
 	}
 }
 
 int read_batch_csums_file(char *buff, int len)
 {
-	static int fdb_open = 1;
 	int bytes_read;
-	char filename[MAXPATHLEN];
-
-	if (fdb_open) {
-		/* Set up file extension */
-		strlcpy(filename, batch_prefix, sizeof(filename));
-		strlcat(filename, rsync_csums_file, sizeof(filename));
-
-		/* Open batch flist file for reading */
-		fdb = do_open(filename, O_RDONLY, 0);
-		if (fdb == -1) {
-			rprintf(FERROR, "Batch file %s open error: %s\n",
-				filename, strerror(errno));
-			close(fdb);
-			exit_cleanup(1);
-		}
-		fdb_open = 0;
-	}
-
-	/* Read csums batch file */
 
-	bytes_read = read(fdb, buff, len);
-
-	if (bytes_read == -1) {
-		rprintf(FERROR, "Batch file %s read error: %s\n",
-			filename, strerror(errno));
-		close(fdb);
+	if ((bytes_read = read(f_csums, buff, len)) < 0) {
+		rprintf(FERROR, "Batch file read error: %s\n", strerror(errno));
+		close(f_csums);
 		exit_cleanup(1);
 	}
-
 	return bytes_read;
 }
 
 void read_batch_csum_info(int flist_entry, struct sum_struct *s,
 			  int *checksums_match)
 {
