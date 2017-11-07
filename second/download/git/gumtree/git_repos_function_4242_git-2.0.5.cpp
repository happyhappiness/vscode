static int matches_merge_filter(struct commit *commit)
{
	int is_merged;

	if (merge_filter == NO_FILTER)
		return 1;

	is_merged = !!(commit->object.flags & UNINTERESTING);
	return (is_merged == (merge_filter == SHOW_MERGED));
}