			return error(FAILED_RUN, prune_worktrees.argv[0]);
	}

	if (run_command_v_opt(rerere.argv, RUN_GIT_CMD))
		return error(FAILED_RUN, rerere.argv[0]);

	report_garbage = report_pack_garbage;
	reprepare_packed_git();
	if (pack_garbage.nr > 0)
		clean_pack_garbage();

	if (auto_gc && too_many_loose_objects())
		warning(_("There are too many unreachable loose objects; "
			"run 'git prune' to remove them."));

	return 0;
}
