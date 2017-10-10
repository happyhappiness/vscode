	printf("%s\n", sub->name);

	return 0;
}

static int clone_submodule(const char *path, const char *gitdir, const char *url,
			   const char *depth, const char *reference, int quiet)
{
	struct child_process cp = CHILD_PROCESS_INIT;

	argv_array_push(&cp.args, "clone");
	argv_array_push(&cp.args, "--no-checkout");
	if (quiet)
		argv_array_push(&cp.args, "--quiet");
	if (depth && *depth)
		argv_array_pushl(&cp.args, "--depth", depth, NULL);
	if (reference && *reference)
		argv_array_pushl(&cp.args, "--reference", reference, NULL);
	if (gitdir && *gitdir)
		argv_array_pushl(&cp.args, "--separate-git-dir", gitdir, NULL);

	argv_array_push(&cp.args, url);
	argv_array_push(&cp.args, path);

