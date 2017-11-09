static int is_common_merge(const struct commit *commit)
{
	return (commit->parents
		&& commit->parents->next
		&& !commit->parents->next->next);
}