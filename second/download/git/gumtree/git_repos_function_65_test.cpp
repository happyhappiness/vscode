void for_each_mergetag(each_mergetag_fn fn, struct commit *commit, void *data)
{
	struct commit_extra_header *extra, *to_free;

	to_free = read_commit_extra_headers(commit, NULL);
	for (extra = to_free; extra; extra = extra->next) {
		if (strcmp(extra->key, "mergetag"))
			continue; /* not a merge tag */
		fn(commit, extra, data);
	}
	free_commit_extra_headers(to_free);
}