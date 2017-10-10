	if (!dry_run) {
		struct string_list refnames = STRING_LIST_INIT_NODUP;

		for (ref = stale_refs; ref; ref = ref->next)
			string_list_append(&refnames, ref->name);

		result = delete_refs(&refnames);
		string_list_clear(&refnames, 0);
	}

	if (verbosity >= 0) {
		for (ref = stale_refs; ref; ref = ref->next) {
			if (!shown_url) {
				fprintf(stderr, _("From %.*s\n"), url_len, url);
				shown_url = 1;
			}
			fprintf(stderr, " x %-*s %-*s -> %s\n",
				TRANSPORT_SUMMARY(_("[deleted]")),
				REFCOL_WIDTH, _("(none)"), prettify_refname(ref->name));
			warn_dangling_symref(stderr, dangling_msg, ref->name);
		}
	}

	free(url);
	free_refs(stale_refs);
