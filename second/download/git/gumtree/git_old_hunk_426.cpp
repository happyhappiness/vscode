	prepare_submodule_repo_env(&cp.env_array);
	cp.no_stdin = 1;

	return run_command(&cp);
}

static int module_clone(int argc, const char **argv, const char *prefix)
{
	const char *name = NULL, *url = NULL;
	const char *reference = NULL, *depth = NULL;
	int quiet = 0;
	FILE *submodule_dot_git;
	char *p, *path = NULL, *sm_gitdir;
	struct strbuf rel_path = STRBUF_INIT;
	struct strbuf sb = STRBUF_INIT;

	struct option module_clone_options[] = {
		OPT_STRING(0, "prefix", &prefix,
			   N_("path"),
			   N_("alternative anchor for relative paths")),
		OPT_STRING(0, "path", &path,
