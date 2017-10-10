	fflush(stdout);
	strbuf_reset(buf);
}

static int push_dav(int nr_spec, char **specs)
{
	struct child_process child = CHILD_PROCESS_INIT;
	size_t i;

	child.git_cmd = 1;
	argv_array_push(&child.args, "http-push");
	argv_array_push(&child.args, "--helper-status");
	if (options.dry_run)
		argv_array_push(&child.args, "--dry-run");
	if (options.verbosity > 1)
		argv_array_push(&child.args, "--verbose");
	argv_array_push(&child.args, url.buf);
	for (i = 0; i < nr_spec; i++)
		argv_array_push(&child.args, specs[i]);

	if (run_command(&child))
		die("git-http-push failed");
	return 0;
}

static int push_git(struct discovery *heads, int nr_spec, char **specs)
{
	struct rpc_state rpc;
