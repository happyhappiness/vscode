static int contains(struct commit *candidate, const struct commit_list *want)
{
	return contains_recurse(candidate, want);
}