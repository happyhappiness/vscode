static int calc_maxwidth(struct ref_array *refs, int remote_bonus)
{
	int i, max = 0;
	for (i = 0; i < refs->nr; i++) {
		struct ref_array_item *it = refs->items[i];
		const char *desc = it->refname;
		int w;

		skip_prefix(it->refname, "refs/heads/", &desc);
		skip_prefix(it->refname, "refs/remotes/", &desc);
		if (it->kind == FILTER_REFS_DETACHED_HEAD) {
			char *head_desc = get_head_description();
			w = utf8_strwidth(head_desc);
			free(head_desc);
		} else
			w = utf8_strwidth(desc);

		if (it->kind == FILTER_REFS_REMOTES)
			w += remote_bonus;
		if (w > max)
			max = w;
	}
	return max;
}