	}
	commit_pager_choice();

	if (!help && get_super_prefix()) {
		if (!(p->option & SUPPORT_SUPER_PREFIX))
			die("%s doesn't support --super-prefix", p->cmd);
		if (prefix)
			die("can't use --super-prefix from a subdirectory");
	}

	if (!help && p->option & NEED_WORK_TREE)
		setup_work_tree();

	trace_argv_printf(argv, "trace: built-in: git");
