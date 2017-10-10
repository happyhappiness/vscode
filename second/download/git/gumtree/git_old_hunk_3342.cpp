	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	err |= run_hook_le(NULL, "post-checkout", sha1_to_hex(null_sha1),
			   sha1_to_hex(sha1), "1", NULL);

	if (!err && option_recursive)
		err = run_command_v_opt(argv_submodule, RUN_GIT_CMD);

	return err;
}

static int write_one_config(const char *key, const char *value, void *data)
{
