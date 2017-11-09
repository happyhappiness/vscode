static int commit_contains(struct ref_filter *filter, struct commit *commit,
			   struct commit_list *list, struct contains_cache *cache)
{
	if (filter->with_commit_tag_algo)
		return contains_tag_algo(commit, list, cache) == CONTAINS_YES;
	return is_descendant_of(commit, list);
}