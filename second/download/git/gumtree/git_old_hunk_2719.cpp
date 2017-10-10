	commit_lock_file(&lock);
	register_tempfile(&pidfile, pidfile_path);
	free(pidfile_path);
	return NULL;
}

static int gc_before_repack(void)
{
	if (pack_refs && run_command_v_opt(pack_refs_cmd.argv, RUN_GIT_CMD))
		return error(FAILED_RUN, pack_refs_cmd.argv[0]);

	if (prune_reflogs && run_command_v_opt(reflog.argv, RUN_GIT_CMD))
