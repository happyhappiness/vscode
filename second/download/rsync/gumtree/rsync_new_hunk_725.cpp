
#include "rsync.h"

extern int verbose;
extern int recurse;
extern int delete_mode;
extern int delete_after;
extern int max_delete;
extern int csum_length;
extern struct stats stats;
extern int dry_run;
extern int am_server;
extern int relative_paths;
extern int preserve_hard_links;
extern int preserve_perms;
extern int cvs_exclude;
extern int io_error;
extern char *tmpdir;
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

static void delete_one(char *fn, int is_dir)
{
	if (!is_dir) {
		if (robust_unlink(fn) != 0) {
			rprintf(FERROR, "delete_one: unlink %s failed: %s\n",
