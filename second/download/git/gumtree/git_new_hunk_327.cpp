			reverse = 1;
		}
		parse_revision_opt(&revs, &ctx, options, blame_opt_usage);
	}
parse_done:
	no_whole_file_rename = !DIFF_OPT_TST(&revs.diffopt, FOLLOW_RENAMES);
	xdl_opts |= revs.diffopt.xdl_opts & (XDF_COMPACTION_HEURISTIC | XDF_INDENT_HEURISTIC);
	DIFF_OPT_CLR(&revs.diffopt, FOLLOW_RENAMES);
	argc = parse_options_end(&ctx);

	if (incremental || (output_option & OUTPUT_PORCELAIN)) {
		if (show_progress > 0)
			die(_("--progress can't be used with --incremental or porcelain formats"));
		show_progress = 0;
	} else if (show_progress < 0)
		show_progress = isatty(2);

	if (0 < abbrev)
		/* one more abbrev length is needed for the boundary commit */
