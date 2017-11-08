static int ref_update_reject_duplicates(struct ref_update **updates, int n,
					struct strbuf *err)
{
	int i;
	for (i = 1; i < n; i++)
		if (!strcmp(updates[i - 1]->refname, updates[i]->refname)) {
			const char *str =
				"Multiple updates for ref '%s' not allowed.";
			if (err)
				strbuf_addf(err, str, updates[i]->refname);

			return 1;
		}
	return 0;
}