	return path;
}

static struct lock_file lock_file;
#define SUBMODULE_WITH_GITDIR ((const char *)1)

int cmd_mv(int argc, const char **argv, const char *prefix)
{
	int i, gitmodules_modified = 0;
	int verbose = 0, show_only = 0, force = 0, ignore_errors = 0;
	struct option builtin_mv_options[] = {
		OPT__VERBOSE(&verbose, N_("be verbose")),
