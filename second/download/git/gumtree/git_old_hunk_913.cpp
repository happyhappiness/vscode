		start_threads(&opt);
	}
#endif

	if (recurse_submodules) {
		gitmodules_config();
		compile_submodule_options(&opt, &pathspec, cached, untracked,
					  opt_exclude, use_index,
					  pattern_type_arg);
	}

	if (show_in_pager && (cached || list.nr))
		die(_("--open-files-in-pager only works on the worktree"));
