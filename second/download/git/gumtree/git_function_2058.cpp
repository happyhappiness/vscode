static int bisect_checkout(char *bisect_rev_hex, int no_checkout)
{

	mark_expected_rev(bisect_rev_hex);

	argv_checkout[2] = bisect_rev_hex;
	if (no_checkout) {
		argv_update_ref[3] = bisect_rev_hex;
		if (run_command_v_opt(argv_update_ref, RUN_GIT_CMD))
			die("update-ref --no-deref HEAD failed on %s",
			    bisect_rev_hex);
	} else {
		int res;
		res = run_command_v_opt(argv_checkout, RUN_GIT_CMD);
		if (res)
			exit(res);
	}

	argv_show_branch[1] = bisect_rev_hex;
	return run_command_v_opt(argv_show_branch, RUN_GIT_CMD);
}