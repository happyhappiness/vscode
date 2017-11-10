int cmd_rev_list(int argc, const char **argv, const char *prefix)
{
	struct rev_info revs;
	struct rev_list_info info;
	int i;
	int bisect_list = 0;
	int bisect_show_vars = 0;
	int bisect_find_all = 0;
	int use_bitmap_index = 0;
	const char *show_progress = NULL;

	git_config(git_default_config, NULL);
	init_revisions(&revs, prefix);
	revs.abbrev = DEFAULT_ABBREV;
	revs.commit_format = CMIT_FMT_UNSPECIFIED;
	argc = setup_revisions(argc, argv, &revs, NULL);

	memset(&info, 0, sizeof(info));
	info.revs = &revs;
	if (revs.bisect)
		bisect_list = 1;

	if (DIFF_OPT_TST(&revs.diffopt, QUICK))
		info.flags |= REV_LIST_QUIET;
	for (i = 1 ; i < argc; i++) {
		const char *arg = argv[i];

		if (!strcmp(arg, "--header")) {
			revs.verbose_header = 1;
			continue;
		}
		if (!strcmp(arg, "--timestamp")) {
			info.show_timestamp = 1;
			continue;
		}
		if (!strcmp(arg, "--bisect")) {
			bisect_list = 1;
			continue;
		}
		if (!strcmp(arg, "--bisect-all")) {
			bisect_list = 1;
			bisect_find_all = 1;
			info.flags |= BISECT_SHOW_ALL;
			revs.show_decorations = 1;
			continue;
		}
		if (!strcmp(arg, "--bisect-vars")) {
			bisect_list = 1;
			bisect_show_vars = 1;
			continue;
		}
		if (!strcmp(arg, "--use-bitmap-index")) {
			use_bitmap_index = 1;
			continue;
		}
		if (!strcmp(arg, "--test-bitmap")) {
			test_bitmap_walk(&revs);
			return 0;
		}
		if (skip_prefix(arg, "--progress=", &arg)) {
			show_progress = arg;
			continue;
		}
		usage(rev_list_usage);

	}
	if (revs.commit_format != CMIT_FMT_UNSPECIFIED) {
		/* The command line has a --pretty  */
		info.hdr_termination = '\n';
		if (revs.commit_format == CMIT_FMT_ONELINE)
			info.header_prefix = "";
		else
			info.header_prefix = "commit ";
	}
	else if (revs.verbose_header)
		/* Only --header was specified */
		revs.commit_format = CMIT_FMT_RAW;

	if ((!revs.commits &&
	     (!(revs.tag_objects || revs.tree_objects || revs.blob_objects) &&
	      !revs.pending.nr)) ||
	    revs.diff)
		usage(rev_list_usage);

	if (revs.show_notes)
		die(_("rev-list does not support display of notes"));

	save_commit_buffer = (revs.verbose_header ||
			      revs.grep_filter.pattern_list ||
			      revs.grep_filter.header_list);
	if (bisect_list)
		revs.limited = 1;

	if (show_progress)
		progress = start_progress_delay(show_progress, 0, 0, 2);

	if (use_bitmap_index && !revs.prune) {
		if (revs.count && !revs.left_right && !revs.cherry_mark) {
			uint32_t commit_count;
			int max_count = revs.max_count;
			if (!prepare_bitmap_walk(&revs)) {
				count_bitmap_commit_list(&commit_count, NULL, NULL, NULL);
				if (max_count >= 0 && max_count < commit_count)
					commit_count = max_count;
				printf("%d\n", commit_count);
				return 0;
			}
		} else if (revs.max_count < 0 &&
			   revs.tag_objects && revs.tree_objects && revs.blob_objects) {
			if (!prepare_bitmap_walk(&revs)) {
				traverse_bitmap_commit_list(&show_object_fast);
				return 0;
			}
		}
	}

	if (prepare_revision_walk(&revs))
		die("revision walk setup failed");
	if (revs.tree_objects)
		mark_edges_uninteresting(&revs, show_edge);

	if (bisect_list) {
		int reaches = reaches, all = all;

		revs.commits = find_bisection(revs.commits, &reaches, &all,
					      bisect_find_all);

		if (bisect_show_vars)
			return show_bisect_vars(&info, reaches, all);
	}

	traverse_commit_list(&revs, show_commit, show_object, &info);

	stop_progress(&progress);

	if (revs.count) {
		if (revs.left_right && revs.cherry_mark)
			printf("%d\t%d\t%d\n", revs.count_left, revs.count_right, revs.count_same);
		else if (revs.left_right)
			printf("%d\t%d\n", revs.count_left, revs.count_right);
		else if (revs.cherry_mark)
			printf("%d\t%d\n", revs.count_left + revs.count_right, revs.count_same);
		else
			printf("%d\n", revs.count_left + revs.count_right);
	}

	return 0;
}