		       ? states.remote->url[0]
		       : _("(no URL)"));

		delete_refs = xmalloc(states.stale.nr * sizeof(*delete_refs));
		for (i = 0; i < states.stale.nr; i++)
			delete_refs[i] = states.stale.items[i].util;
		if (!dry_run)
			result |= repack_without_refs(delete_refs,
						      states.stale.nr, NULL);
		free(delete_refs);
	}

	for (i = 0; i < states.stale.nr; i++) {
		const char *refname = states.stale.items[i].util;

