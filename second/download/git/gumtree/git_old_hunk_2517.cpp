		;

	url_len = i + 1;
	if (4 < i && !strncmp(".git", url + i - 3, 4))
		url_len = i - 3;

	for (ref = stale_refs; ref; ref = ref->next) {
		if (!dry_run)
			result |= delete_ref(ref->name, NULL, 0);
		if (verbosity >= 0 && !shown_url) {
			fprintf(stderr, _("From %.*s\n"), url_len, url);
			shown_url = 1;
		}
		if (verbosity >= 0) {
			fprintf(stderr, " x %-*s %-*s -> %s\n",
				TRANSPORT_SUMMARY(_("[deleted]")),
				REFCOL_WIDTH, _("(none)"), prettify_refname(ref->name));
			warn_dangling_symref(stderr, dangling_msg, ref->name);
		}
	}
