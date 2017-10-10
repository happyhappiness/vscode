	sigchain_push_common(remove_pidfile_on_signal);
	atexit(remove_pidfile);

	return NULL;
}

static int gc_before_repack(void)
{
	if (pack_refs && run_command_v_opt(pack_refs_cmd.argv, RUN_GIT_CMD))
		return error(FAILED_RUN, pack_refs_cmd.argv[0]);

	if (prune_reflogs && run_command_v_opt(reflog.argv, RUN_GIT_CMD))
		return error(FAILED_RUN, reflog.argv[0]);

	pack_refs = 0;
	prune_reflogs = 0;
	return 0;
}

int cmd_gc(int argc, const char **argv, const char *prefix)
{
	int aggressive = 0;
	int auto_gc = 0;
	int quiet = 0;
	int force = 0;
