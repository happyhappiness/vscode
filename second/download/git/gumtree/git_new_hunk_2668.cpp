		if (!gitmodules_is_unmerged)
			git_config_from_file(submodule_config, gitmodules_path.buf, NULL);
		strbuf_release(&gitmodules_path);
	}
}

void handle_ignore_submodules_arg(struct diff_options *diffopt,
				  const char *arg)
{
	DIFF_OPT_CLR(diffopt, IGNORE_SUBMODULES);
	DIFF_OPT_CLR(diffopt, IGNORE_UNTRACKED_IN_SUBMODULES);
	DIFF_OPT_CLR(diffopt, IGNORE_DIRTY_SUBMODULES);
