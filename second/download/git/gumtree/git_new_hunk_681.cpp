					opt.pattern_list->pattern);
			string_list_append(&path_list, buf.buf);
			strbuf_detach(&buf, NULL);
		}
	}

	if (recurse_submodules && (!use_index || untracked))
		die(_("option not supported with --recurse-submodules."));

	if (!show_in_pager && !opt.status_only)
		setup_pager();

	if (!use_index && (untracked || cached))
		die(_("--cached or --untracked cannot be used with --no-index."));

