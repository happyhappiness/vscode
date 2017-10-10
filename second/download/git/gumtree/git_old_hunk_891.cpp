	hashmap_init(&names, (hashmap_cmp_fn) commit_name_cmp, 0);
	for_each_rawref(get_name, NULL);
	if (!names.size && !always)
		die(_("No names found, cannot describe anything."));

	if (argc == 0) {
		if (dirty) {
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
				dirty = NULL;
		}
		describe("HEAD", 1);
	} else if (dirty) {
		die(_("--dirty is incompatible with commit-ishes"));
	} else {
		while (argc-- > 0)
			describe(*argv++, argc == 0);
	}
	return 0;
}
