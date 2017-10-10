		if (!file_exists(path))
			die_errno("cannot stat path '%s'", path);
	}

	revs.disable_stdin = 1;
	setup_revisions(argc, argv, &revs, NULL);

	init_scoreboard(&sb);
	sb.revs = &revs;
	sb.contents_from = contents_from;
	sb.reverse = reverse;
	setup_scoreboard(&sb, path, &o);
	lno = sb.num_lines;

	if (lno && !range_list.nr)
		string_list_append(&range_list, "1");

	anchor = 1;
	range_set_init(&ranges, range_list.nr);
