static void show_mergetag(struct rev_info *opt, struct commit *commit)
{
	struct commit_extra_header *extra, *to_free;

	to_free = read_commit_extra_headers(commit, NULL);
	for (extra = to_free; extra; extra = extra->next) {
		if (strcmp(extra->key, "mergetag"))
			continue; /* not a merge tag */
		show_one_mergetag(opt, extra, commit);
	}
	free_commit_extra_headers(to_free);
}