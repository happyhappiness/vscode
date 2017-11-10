static inline int single_parent(struct commit *commit)
{
	return commit->parents && !commit->parents->next;
}