		rollback_lock_file(&head_lock);
		return error(_("failed to finalize '%s'."), git_path_head_file());
	}
	return 0;
}

static int reset_for_rollback(const unsigned char *sha1)
{
	const char *argv[4];	/* reset --merge <arg> + NULL */
	argv[0] = "reset";
	argv[1] = "--merge";
	argv[2] = sha1_to_hex(sha1);
	argv[3] = NULL;
	return run_command_v_opt(argv, RUN_GIT_CMD);
}
