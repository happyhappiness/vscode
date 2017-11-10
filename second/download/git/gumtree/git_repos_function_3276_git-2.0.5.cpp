static struct ref *get_expanded_map(const struct ref *remote_refs,
				    const struct refspec *refspec)
{
	const struct ref *ref;
	struct ref *ret = NULL;
	struct ref **tail = &ret;

	for (ref = remote_refs; ref; ref = ref->next) {
		char *expn_name = NULL;

		if (strchr(ref->name, '^'))
			continue; /* a dereference item */
		if (match_name_with_pattern(refspec->src, ref->name,
					    refspec->dst, &expn_name) &&
		    !ignore_symref_update(expn_name)) {
			struct ref *cpy = copy_ref(ref);

			cpy->peer_ref = alloc_ref(expn_name);
			if (refspec->force)
				cpy->peer_ref->force = 1;
			*tail = cpy;
			tail = &cpy->next;
		}
		free(expn_name);
	}

	return ret;
}