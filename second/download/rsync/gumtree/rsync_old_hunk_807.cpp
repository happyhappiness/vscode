		set_filter_dir("/", 1);
	} else
		set_filter_dir(lp_path(i), module_dirlen);

	p = lp_filter(i);
	parse_rule(&server_filter_list, p, MATCHFLG_WORD_SPLIT,
		   XFLG_ANCHORED2ABS);

	p = lp_include_from(i);
	parse_filter_file(&server_filter_list, p, MATCHFLG_INCLUDE,
	    XFLG_ANCHORED2ABS | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);

	p = lp_include(i);
	parse_rule(&server_filter_list, p,
		   MATCHFLG_INCLUDE | MATCHFLG_WORD_SPLIT,
		   XFLG_ANCHORED2ABS | XFLG_OLD_PREFIXES);

	p = lp_exclude_from(i);
	parse_filter_file(&server_filter_list, p, 0,
	    XFLG_ANCHORED2ABS | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);

	p = lp_exclude(i);
	parse_rule(&server_filter_list, p, MATCHFLG_WORD_SPLIT,
		   XFLG_ANCHORED2ABS | XFLG_OLD_PREFIXES);

	log_init();

	if (use_chroot) {
		/*
		 * XXX: The 'use chroot' flag is a fairly reliable
		 * source of confusion, because it fails under two
		 * important circumstances: running as non-root,
		 * running on Win32 (or possibly others).  On the
