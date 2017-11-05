struct ref *guess_remote_head(const struct ref *head,
			      const struct ref *refs,
			      int all)
{
	const struct ref *r;
	struct ref *list = NULL;
	struct ref **tail = &list;

	if (!head)
		return NULL;

	/*
	 * Some transports support directly peeking at
	 * where HEAD points; if that is the case, then
	 * we don't have to guess.
	 */
	if (head->symref)
		return copy_ref(find_ref_by_name(refs, head->symref));

	/* If refs/heads/master could be right, it is. */
	if (!all) {
		r = find_ref_by_name(refs, "refs/heads/master");
		if (r && !hashcmp(r->old_sha1, head->old_sha1))
			return copy_ref(r);
	}

	/* Look for another ref that points there */
	for (r = refs; r; r = r->next) {
		if (r != head &&
		    starts_with(r->name, "refs/heads/") &&
		    !hashcmp(r->old_sha1, head->old_sha1)) {
			*tail = copy_ref(r);
			tail = &((*tail)->next);
			if (!all)
				break;
		}
	}

	return list;
}