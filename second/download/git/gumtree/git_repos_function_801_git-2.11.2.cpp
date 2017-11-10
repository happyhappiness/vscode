int in_merge_bases_many(struct commit *commit, int nr_reference, struct commit **reference)
{
	struct commit_list *bases;
	int ret = 0, i;

	if (parse_commit(commit))
		return ret;
	for (i = 0; i < nr_reference; i++)
		if (parse_commit(reference[i]))
			return ret;

	bases = paint_down_to_common(commit, nr_reference, reference);
	if (commit->object.flags & PARENT2)
		ret = 1;
	clear_commit_marks(commit, all_flags);
	clear_commit_marks_many(nr_reference, reference, all_flags);
	free_commit_list(bases);
	return ret;
}