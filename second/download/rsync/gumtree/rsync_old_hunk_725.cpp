
#include "rsync.h"

extern int verbose;
extern int recurse;
extern int delete_mode;
extern int protocol_version;
extern int csum_length;
extern struct stats stats;
extern int dry_run;
extern int am_server;
extern int relative_paths;
extern int preserve_hard_links;
extern int cvs_exclude;
extern int io_error;
extern char *tmpdir;
extern char *compare_dest;
extern int make_backups;
extern int do_progress;
extern char *backup_dir;
extern char *backup_suffix;
extern int backup_suffix_len;

static struct delete_list {
	DEV64_T dev;
	INO64_T inode;
} *delete_list;
static int dlist_len, dlist_alloc_len;

/* yuck! This function wouldn't have been necessary if I had the sorting
 * algorithm right. Unfortunately fixing the sorting algorithm would introduce
 * a backward incompatibility as file list indexes are sent over the link.
 */
static int delete_already_done(struct file_list *flist,int j)
{
	int i;
	STRUCT_STAT st;

	if (link_stat(f_name(flist->files[j]), &st)) return 1;

	for (i = 0; i < dlist_len; i++) {
		if (st.st_ino == delete_list[i].inode &&
		    (DEV64_T)st.st_dev == delete_list[i].dev)
			return 1;
	}

	return 0;
}

static void add_delete_entry(struct file_struct *file)
{
	if (dlist_len == dlist_alloc_len) {
		dlist_alloc_len += 1024;
		delete_list = realloc_array(delete_list, struct delete_list,
					    dlist_alloc_len);
		if (!delete_list) out_of_memory("add_delete_entry");
	}

	delete_list[dlist_len].dev = file->dev;
	delete_list[dlist_len].inode = file->inode;
	dlist_len++;

	if (verbose > 3)
		rprintf(FINFO,"added %s to delete list\n", f_name(file));
}

static void delete_one(char *fn, int is_dir)
{
	if (!is_dir) {
		if (robust_unlink(fn) != 0) {
			rprintf(FERROR, "delete_one: unlink %s failed: %s\n",
