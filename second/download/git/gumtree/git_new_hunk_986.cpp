		}
		strbuf_release(&unquoted);
		strbuf_release(&buf);
	}

	if (split_index > 0) {
		if (git_config_get_split_index() == 0)
			warning(_("core.splitIndex is set to false; "
				  "remove or change it, if you really want to "
				  "enable split index"));
		if (the_index.split_index)
			the_index.cache_changed |= SPLIT_INDEX_ORDERED;
		else
			add_split_index(&the_index);
	} else if (!split_index) {
		if (git_config_get_split_index() == 1)
			warning(_("core.splitIndex is set to true; "
				  "remove or change it, if you really want to "
				  "disable split index"));
		remove_split_index(&the_index);
	}

	switch (untracked_cache) {
	case UC_UNSPECIFIED:
		break;
	case UC_DISABLE:
