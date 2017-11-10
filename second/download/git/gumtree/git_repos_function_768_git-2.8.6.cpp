int in_merge_bases(struct commit *commit, struct commit *reference)
{
	return in_merge_bases_many(commit, 1, &reference);
}