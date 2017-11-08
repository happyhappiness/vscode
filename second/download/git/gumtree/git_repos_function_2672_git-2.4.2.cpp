static int ref_update_reject_duplicates(struct ref_update **updates, int n,
					struct strbuf *err)
{
	int i;

	assert(err);

	for (i = 1; i < n; i++)
		if (!strcmp(updates[i - 1]->refname, updates[i]->refname)) {
			strbuf_addf(err,
				    "Multiple updates for ref '%s' not allowed.",
				    updates[i]->refname);
			return 1;
		}
	return 0;
}