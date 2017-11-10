static const char *map_refspec(const char *ref,
			       struct remote *remote, struct ref *local_refs)
{
	struct ref *matched = NULL;

	/* Does "ref" uniquely name our ref? */
	if (count_refspec_match(ref, local_refs, &matched) != 1)
		return ref;

	if (remote->push) {
		struct refspec query;
		memset(&query, 0, sizeof(struct refspec));
		query.src = matched->name;
		if (!query_refspecs(remote->push, remote->push_refspec_nr, &query) &&
		    query.dst) {
			struct strbuf buf = STRBUF_INIT;
			strbuf_addf(&buf, "%s%s:%s",
				    query.force ? "+" : "",
				    query.src, query.dst);
			return strbuf_detach(&buf, NULL);
		}
	}

	if (push_default == PUSH_DEFAULT_UPSTREAM &&
	    starts_with(matched->name, "refs/heads/")) {
		struct branch *branch = branch_get(matched->name + 11);
		if (branch->merge_nr == 1 && branch->merge[0]->src) {
			struct strbuf buf = STRBUF_INIT;
			strbuf_addf(&buf, "%s:%s",
				    ref, branch->merge[0]->src);
			return strbuf_detach(&buf, NULL);
		}
	}

	return ref;
}