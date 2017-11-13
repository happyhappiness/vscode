int cmd_blame(int argc, const char **argv, const char *prefix)
{
	struct rev_info revs;
	const char *path;
	struct scoreboard sb;
	struct origin *o;
	struct blame_entry *ent = NULL;
	long dashdash_pos, lno;
	char *final_commit_name = NULL;
	enum object_type type;
	struct commit *final_commit = NULL;

	struct string_list range_list = STRING_LIST_INIT_NODUP;
	int output_option = 0, opt = 0;
	int show_stats = 0;
	const char *revs_file = NULL;
	const char *contents_from = NULL;
	const struct option options[] = {
		OPT_BOOL(0, "incremental", &incremental, N_("Show blame entries as we find them, incrementally")),
		OPT_BOOL('b', NULL, &blank_boundary, N_("Show blank SHA-1 for boundary commits (Default: off)")),
		OPT_BOOL(0, "root", &show_root, N_("Do not treat root commits as boundaries (Default: off)")),
		OPT_BOOL(0, "show-stats", &show_stats, N_("Show work cost statistics")),
		OPT_BOOL(0, "progress", &show_progress, N_("Force progress reporting")),
		OPT_BIT(0, "score-debug", &output_option, N_("Show output score for blame entries"), OUTPUT_SHOW_SCORE),
		OPT_BIT('f', "show-name", &output_option, N_("Show original filename (Default: auto)"), OUTPUT_SHOW_NAME),
		OPT_BIT('n', "show-number", &output_option, N_("Show original linenumber (Default: off)"), OUTPUT_SHOW_NUMBER),
		OPT_BIT('p', "porcelain", &output_option, N_("Show in a format designed for machine consumption"), OUTPUT_PORCELAIN),
		OPT_BIT(0, "line-porcelain", &output_option, N_("Show porcelain format with per-line commit information"), OUTPUT_PORCELAIN|OUTPUT_LINE_PORCELAIN),
		OPT_BIT('c', NULL, &output_option, N_("Use the same output mode as git-annotate (Default: off)"), OUTPUT_ANNOTATE_COMPAT),
		OPT_BIT('t', NULL, &output_option, N_("Show raw timestamp (Default: off)"), OUTPUT_RAW_TIMESTAMP),
		OPT_BIT('l', NULL, &output_option, N_("Show long commit SHA1 (Default: off)"), OUTPUT_LONG_OBJECT_NAME),
		OPT_BIT('s', NULL, &output_option, N_("Suppress author name and timestamp (Default: off)"), OUTPUT_NO_AUTHOR),
		OPT_BIT('e', "show-email", &output_option, N_("Show author email instead of name (Default: off)"), OUTPUT_SHOW_EMAIL),
		OPT_BIT('w', NULL, &xdl_opts, N_("Ignore whitespace differences"), XDF_IGNORE_WHITESPACE),
		OPT_BIT(0, "minimal", &xdl_opts, N_("Spend extra cycles to find better match"), XDF_NEED_MINIMAL),
		OPT_STRING('S', NULL, &revs_file, N_("file"), N_("Use revisions from <file> instead of calling git-rev-list")),
		OPT_STRING(0, "contents", &contents_from, N_("file"), N_("Use <file>'s contents as the final image")),
		{ OPTION_CALLBACK, 'C', NULL, &opt, N_("score"), N_("Find line copies within and across files"), PARSE_OPT_OPTARG, blame_copy_callback },
		{ OPTION_CALLBACK, 'M', NULL, &opt, N_("score"), N_("Find line movements within and across files"), PARSE_OPT_OPTARG, blame_move_callback },
		OPT_STRING_LIST('L', NULL, &range_list, N_("n,m"), N_("Process only line range n,m, counting from 1")),
		OPT__ABBREV(&abbrev),
		OPT_END()
	};

	struct parse_opt_ctx_t ctx;
	int cmd_is_annotate = !strcmp(argv[0], "annotate");
	struct range_set ranges;
	unsigned int range_i;
	long anchor;

	git_config(git_blame_config, &output_option);
	init_revisions(&revs, NULL);
	revs.date_mode = blame_date_mode;
	DIFF_OPT_SET(&revs.diffopt, ALLOW_TEXTCONV);
	DIFF_OPT_SET(&revs.diffopt, FOLLOW_RENAMES);

	save_commit_buffer = 0;
	dashdash_pos = 0;
	show_progress = -1;

	parse_options_start(&ctx, argc, argv, prefix, options,
			    PARSE_OPT_KEEP_DASHDASH | PARSE_OPT_KEEP_ARGV0);
	for (;;) {
		switch (parse_options_step(&ctx, options, blame_opt_usage)) {
		case PARSE_OPT_HELP:
			exit(129);
		case PARSE_OPT_DONE:
			if (ctx.argv[0])
				dashdash_pos = ctx.cpidx;
			goto parse_done;
		}

		if (!strcmp(ctx.argv[0], "--reverse")) {
			ctx.argv[0] = "--children";
			reverse = 1;
		}
		parse_revision_opt(&revs, &ctx, options, blame_opt_usage);
	}
parse_done:
	no_whole_file_rename = !DIFF_OPT_TST(&revs.diffopt, FOLLOW_RENAMES);
	DIFF_OPT_CLR(&revs.diffopt, FOLLOW_RENAMES);
	argc = parse_options_end(&ctx);

	if (incremental || (output_option & OUTPUT_PORCELAIN)) {
		if (show_progress > 0)
			die("--progress can't be used with --incremental or porcelain formats");
		show_progress = 0;
	} else if (show_progress < 0)
		show_progress = isatty(2);

	if (0 < abbrev)
		/* one more abbrev length is needed for the boundary commit */
		abbrev++;

	if (revs_file && read_ancestry(revs_file))
		die_errno("reading graft file '%s' failed", revs_file);

	if (cmd_is_annotate) {
		output_option |= OUTPUT_ANNOTATE_COMPAT;
		blame_date_mode.type = DATE_ISO8601;
	} else {
		blame_date_mode = revs.date_mode;
	}

	/* The maximum width used to show the dates */
	switch (blame_date_mode.type) {
	case DATE_RFC2822:
		blame_date_width = sizeof("Thu, 19 Oct 2006 16:00:04 -0700");
		break;
	case DATE_ISO8601_STRICT:
		blame_date_width = sizeof("2006-10-19T16:00:04-07:00");
		break;
	case DATE_ISO8601:
		blame_date_width = sizeof("2006-10-19 16:00:04 -0700");
		break;
	case DATE_RAW:
		blame_date_width = sizeof("1161298804 -0700");
		break;
	case DATE_UNIX:
		blame_date_width = sizeof("1161298804");
		break;
	case DATE_SHORT:
		blame_date_width = sizeof("2006-10-19");
		break;
	case DATE_RELATIVE:
		/* TRANSLATORS: This string is used to tell us the maximum
		   display width for a relative timestamp in "git blame"
		   output.  For C locale, "4 years, 11 months ago", which
		   takes 22 places, is the longest among various forms of
		   relative timestamps, but your language may need more or
		   fewer display columns. */
		blame_date_width = utf8_strwidth(_("4 years, 11 months ago")) + 1; /* add the null */
		break;
	case DATE_NORMAL:
		blame_date_width = sizeof("Thu Oct 19 16:00:04 2006 -0700");
		break;
	case DATE_STRFTIME:
		blame_date_width = strlen(show_date(0, 0, &blame_date_mode)) + 1; /* add the null */
		break;
	}
	blame_date_width -= 1; /* strip the null */

	if (DIFF_OPT_TST(&revs.diffopt, FIND_COPIES_HARDER))
		opt |= (PICKAXE_BLAME_COPY | PICKAXE_BLAME_MOVE |
			PICKAXE_BLAME_COPY_HARDER);

	if (!blame_move_score)
		blame_move_score = BLAME_DEFAULT_MOVE_SCORE;
	if (!blame_copy_score)
		blame_copy_score = BLAME_DEFAULT_COPY_SCORE;

	/*
	 * We have collected options unknown to us in argv[1..unk]
	 * which are to be passed to revision machinery if we are
	 * going to do the "bottom" processing.
	 *
	 * The remaining are:
	 *
	 * (1) if dashdash_pos != 0, it is either
	 *     "blame [revisions] -- <path>" or
	 *     "blame -- <path> <rev>"
	 *
	 * (2) otherwise, it is one of the two:
	 *     "blame [revisions] <path>"
	 *     "blame <path> <rev>"
	 *
	 * Note that we must strip out <path> from the arguments: we do not
	 * want the path pruning but we may want "bottom" processing.
	 */
	if (dashdash_pos) {
		switch (argc - dashdash_pos - 1) {
		case 2: /* (1b) */
			if (argc != 4)
				usage_with_options(blame_opt_usage, options);
			/* reorder for the new way: <rev> -- <path> */
			argv[1] = argv[3];
			argv[3] = argv[2];
			argv[2] = "--";
			/* FALLTHROUGH */
		case 1: /* (1a) */
			path = add_prefix(prefix, argv[--argc]);
			argv[argc] = NULL;
			break;
		default:
			usage_with_options(blame_opt_usage, options);
		}
	} else {
		if (argc < 2)
			usage_with_options(blame_opt_usage, options);
		path = add_prefix(prefix, argv[argc - 1]);
		if (argc == 3 && !file_exists(path)) { /* (2b) */
			path = add_prefix(prefix, argv[1]);
			argv[1] = argv[2];
		}
		argv[argc - 1] = "--";

		setup_work_tree();
		if (!file_exists(path))
			die_errno("cannot stat path '%s'", path);
	}

	revs.disable_stdin = 1;
	setup_revisions(argc, argv, &revs, NULL);
	memset(&sb, 0, sizeof(sb));

	sb.revs = &revs;
	if (!reverse) {
		final_commit_name = prepare_final(&sb);
		sb.commits.compare = compare_commits_by_commit_date;
	}
	else if (contents_from)
		die("--contents and --reverse do not blend well.");
	else {
		final_commit_name = prepare_initial(&sb);
		sb.commits.compare = compare_commits_by_reverse_commit_date;
		if (revs.first_parent_only)
			revs.children.name = NULL;
	}

	if (!sb.final) {
		/*
		 * "--not A B -- path" without anything positive;
		 * do not default to HEAD, but use the working tree
		 * or "--contents".
		 */
		setup_work_tree();
		sb.final = fake_working_tree_commit(&sb.revs->diffopt,
						    path, contents_from);
		add_pending_object(&revs, &(sb.final->object), ":");
	}
	else if (contents_from)
		die("Cannot use --contents with final commit object name");

	if (reverse && revs.first_parent_only) {
		final_commit = find_single_final(sb.revs, NULL);
		if (!final_commit)
			die("--reverse and --first-parent together require specified latest commit");
	}

	/*
	 * If we have bottom, this will mark the ancestors of the
	 * bottom commits we would reach while traversing as
	 * uninteresting.
	 */
	if (prepare_revision_walk(&revs))
		die(_("revision walk setup failed"));

	if (reverse && revs.first_parent_only) {
		struct commit *c = final_commit;

		sb.revs->children.name = "children";
		while (c->parents &&
		       oidcmp(&c->object.oid, &sb.final->object.oid)) {
			struct commit_list *l = xcalloc(1, sizeof(*l));

			l->item = c;
			if (add_decoration(&sb.revs->children,
					   &c->parents->item->object, l))
				die("BUG: not unique item in first-parent chain");
			c = c->parents->item;
		}

		if (oidcmp(&c->object.oid, &sb.final->object.oid))
			die("--reverse --first-parent together require range along first-parent chain");
	}

	if (is_null_oid(&sb.final->object.oid)) {
		o = sb.final->util;
		sb.final_buf = xmemdupz(o->file.ptr, o->file.size);
		sb.final_buf_size = o->file.size;
	}
	else {
		o = get_origin(&sb, sb.final, path);
		if (fill_blob_sha1_and_mode(o))
			die("no such path %s in %s", path, final_commit_name);

		if (DIFF_OPT_TST(&sb.revs->diffopt, ALLOW_TEXTCONV) &&
		    textconv_object(path, o->mode, o->blob_sha1, 1, (char **) &sb.final_buf,
				    &sb.final_buf_size))
			;
		else
			sb.final_buf = read_sha1_file(o->blob_sha1, &type,
						      &sb.final_buf_size);

		if (!sb.final_buf)
			die("Cannot read blob %s for path %s",
			    sha1_to_hex(o->blob_sha1),
			    path);
	}
	num_read_blob++;
	lno = prepare_lines(&sb);

	if (lno && !range_list.nr)
		string_list_append(&range_list, "1");

	anchor = 1;
	range_set_init(&ranges, range_list.nr);
	for (range_i = 0; range_i < range_list.nr; ++range_i) {
		long bottom, top;
		if (parse_range_arg(range_list.items[range_i].string,
				    nth_line_cb, &sb, lno, anchor,
				    &bottom, &top, sb.path))
			usage(blame_usage);
		if (lno < top || ((lno || bottom) && lno < bottom))
			die("file %s has only %lu lines", path, lno);
		if (bottom < 1)
			bottom = 1;
		if (top < 1)
			top = lno;
		bottom--;
		range_set_append_unsafe(&ranges, bottom, top);
		anchor = top + 1;
	}
	sort_and_merge_range_set(&ranges);

	for (range_i = ranges.nr; range_i > 0; --range_i) {
		const struct range *r = &ranges.ranges[range_i - 1];
		long bottom = r->start;
		long top = r->end;
		struct blame_entry *next = ent;
		ent = xcalloc(1, sizeof(*ent));
		ent->lno = bottom;
		ent->num_lines = top - bottom;
		ent->suspect = o;
		ent->s_lno = bottom;
		ent->next = next;
		origin_incref(o);
	}

	o->suspects = ent;
	prio_queue_put(&sb.commits, o->commit);

	origin_decref(o);

	range_set_release(&ranges);
	string_list_clear(&range_list, 0);

	sb.ent = NULL;
	sb.path = path;

	read_mailmap(&mailmap, NULL);

	assign_blame(&sb, opt);

	if (!incremental)
		setup_pager();

	free(final_commit_name);

	if (incremental)
		return 0;

	sb.ent = blame_sort(sb.ent, compare_blame_final);

	coalesce(&sb);

	if (!(output_option & OUTPUT_PORCELAIN))
		find_alignment(&sb, &output_option);

	output(&sb, output_option);
	free((void *)sb.final_buf);
	for (ent = sb.ent; ent; ) {
		struct blame_entry *e = ent->next;
		free(ent);
		ent = e;
	}

	if (show_stats) {
		printf("num read blob: %d\n", num_read_blob);
		printf("num get patch: %d\n", num_get_patch);
		printf("num commits: %d\n", num_commits);
	}
	return 0;
}