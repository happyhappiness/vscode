		       ? states.remote->url[0]
		       : _("(no URL)"));

		delete_refs = xmalloc(states.stale.nr * sizeof(*delete_refs));
		for (i = 0; i < states.stale.nr; i++)
			delete_refs[i] = states.stale.items[i].util;
		if (!dry_run) {
			struct strbuf err = STRBUF_INIT;
			if (repack_without_refs(delete_refs, states.stale.nr,
						&err))
				result |= error("%s", err.buf);
			strbuf_release(&err);
		}
		free(delete_refs);
	}

	for (i = 0; i < states.stale.nr; i++) {
		const char *refname = states.stale.items[i].util;

