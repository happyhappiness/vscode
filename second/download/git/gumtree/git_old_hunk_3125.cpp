	}
parse_done:
	no_whole_file_rename = !DIFF_OPT_TST(&revs.diffopt, FOLLOW_RENAMES);
	DIFF_OPT_CLR(&revs.diffopt, FOLLOW_RENAMES);
	argc = parse_options_end(&ctx);

	if (0 < abbrev)
		/* one more abbrev length is needed for the boundary commit */
		abbrev++;

	if (revs_file && read_ancestry(revs_file))
		die_errno("reading graft file '%s' failed", revs_file);
