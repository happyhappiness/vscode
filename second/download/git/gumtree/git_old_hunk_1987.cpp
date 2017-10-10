	strbuf_release(&buf2);
	return result;
}

static int prune_remote(const char *remote, int dry_run)
{
	int result = 0, i;
	struct ref_states states;
	struct string_list delete_refs_list = STRING_LIST_INIT_NODUP;
	const char **delete_refs;
	const char *dangling_msg = dry_run
		? _(" %s will become dangling!")
		: _(" %s has become dangling!");

	memset(&states, 0, sizeof(states));
	get_remote_ref_states(remote, &states, GET_REF_STATES);

	if (states.stale.nr) {
		printf_ln(_("Pruning %s"), remote);
		printf_ln(_("URL: %s"),
		       states.remote->url_nr
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

		string_list_insert(&delete_refs_list, refname);

		if (!dry_run)
			result |= delete_ref(refname, NULL, 0);

		if (dry_run)
			printf_ln(_(" * [would prune] %s"),
			       abbrev_ref(refname, "refs/remotes/"));
		else
			printf_ln(_(" * [pruned] %s"),
			       abbrev_ref(refname, "refs/remotes/"));
	}

	warn_dangling_symrefs(stdout, dangling_msg, &delete_refs_list);
	string_list_clear(&delete_refs_list, 0);

	free_remote_ref_states(&states);
	return result;
}

static int prune(int argc, const char **argv)
{
