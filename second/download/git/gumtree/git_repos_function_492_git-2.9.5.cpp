static int commit_contains(struct ref_filter *filter, struct commit *commit)
{
	if (filter->with_commit_tag_algo)
		return contains_tag_algo(commit, filter->with_commit);
	return is_descendant_of(commit, filter->with_commit);
}