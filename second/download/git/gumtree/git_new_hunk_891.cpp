	hashmap_init(&names, (hashmap_cmp_fn) commit_name_cmp, 0);
	for_each_rawref(get_name, NULL);
	if (!names.size && !always)
		die(_("No names found, cannot describe anything."));

	if (argc == 0) {
		if (broken) {
			struct child_process cp = CHILD_PROCESS_INIT;
			argv_array_pushv(&cp.args, diff_index_args);
			cp.git_cmd = 1;
			cp.no_stdin = 1;
			cp.no_stdout = 1;

			if (!dirty)
				dirty = "-dirty";

			switch (run_command(&cp)) {
			case 0:
				suffix = NULL;
				break;
			case 1:
				suffix = dirty;
				break;
			default:
				/* diff-index aborted abnormally */
				suffix = broken;
			}
		} else if (dirty) {
			static struct lock_file index_lock;
			int fd;

			read_cache_preload(NULL);
			refresh_index(&the_index, REFRESH_QUIET|REFRESH_UNMERGED,
				      NULL, NULL, NULL);
			fd = hold_locked_index(&index_lock, 0);
			if (0 <= fd)
				update_index_if_able(&the_index, &index_lock);

			if (!cmd_diff_index(ARRAY_SIZE(diff_index_args) - 1,
					    diff_index_args, prefix))
				suffix = NULL;
			else
				suffix = dirty;
		}
		describe("HEAD", 1);
	} else if (dirty) {
		die(_("--dirty is incompatible with commit-ishes"));
	} else if (broken) {
		die(_("--broken is incompatible with commit-ishes"));
	} else {
		while (argc-- > 0)
			describe(*argv++, argc == 0);
	}
	return 0;
}
