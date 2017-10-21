   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "rsync.h"

extern int verbose;
extern int recurse;
extern int delete_after;
extern int max_delete;
extern int csum_length;
extern struct stats stats;
extern int dry_run;
extern int read_batch;
extern int batch_gen_fd;
extern int am_server;
extern int relative_paths;
extern int keep_dirlinks;
extern int preserve_hard_links;
extern int preserve_perms;
extern int cvs_exclude;
extern int io_error;
extern char *tmpdir;
extern char *partial_dir;
extern char *compare_dest;
extern int make_backups;
extern int do_progress;
extern char *backup_dir;
extern char *backup_suffix;
extern int backup_suffix_len;
extern int cleanup_got_literal;
extern int module_id;
extern int ignore_errors;
extern int orig_umask;
extern int keep_partial;
extern int checksum_seed;
extern int inplace;

extern struct exclude_list_struct server_exclude_list;


static void delete_one(char *fn, int is_dir)
{
	if (!is_dir) {
		if (robust_unlink(fn) != 0) {
			rsyserr(FERROR, errno, "delete_one: unlink %s failed",
				full_fname(fn));
		} else if (verbose)
			rprintf(FINFO, "deleting %s\n", safe_fname(fn));
	} else {
		if (do_rmdir(fn) != 0) {
			if (errno != ENOTEMPTY && errno != EEXIST) {
				rsyserr(FERROR, errno,
					"delete_one: rmdir %s failed",
					full_fname(fn));
			}
		} else if (verbose) {
			rprintf(FINFO, "deleting directory %s\n",
				safe_fname(fn));
		}
	}
}


static int is_backup_file(char *fn)
{
	int k = strlen(fn) - backup_suffix_len;
	return k > 0 && strcmp(fn+k, backup_suffix) == 0;
}


/* This deletes any files on the receiving side that are not present
 * on the sending side. */
void delete_files(struct file_list *flist)
{
	struct file_list *local_file_list;
	int i, j;
	char *argv[1], fbuf[MAXPATHLEN];
	static int deletion_count;

	if (cvs_exclude)
		add_cvs_excludes();

	if (io_error && !(lp_ignore_errors(module_id) || ignore_errors)) {
		rprintf(FINFO,"IO error encountered - skipping file deletion\n");
		return;
	}

	for (j = 0; j < flist->count; j++) {
		if (!(flist->files[j]->flags & FLAG_TOP_DIR)
		    || !S_ISDIR(flist->files[j]->mode))
			continue;

		argv[0] = f_name_to(flist->files[j], fbuf);

		if (!(local_file_list = send_file_list(-1, 1, argv)))
			continue;

		if (verbose > 1)
			rprintf(FINFO, "deleting in %s\n", safe_fname(fbuf));

		for (i = local_file_list->count-1; i >= 0; i--) {
			if (max_delete && deletion_count > max_delete)
				break;
			if (!local_file_list->files[i]->basename)
				continue;
			if (flist_find(flist,local_file_list->files[i]) < 0) {
				char *f = f_name(local_file_list->files[i]);
				if (make_backups && (backup_dir || !is_backup_file(f))) {
					make_backup(f);
					if (verbose) {
						rprintf(FINFO, "deleting %s\n",
							safe_fname(f));
					}
				} else {
					int mode = local_file_list->files[i]->mode;
					delete_one(f, S_ISDIR(mode) != 0);
				}
				deletion_count++;
			}
		}
		flist_free(local_file_list);
	}
}


/*
 * get_tmpname() - create a tmp filename for a given filename
 *
