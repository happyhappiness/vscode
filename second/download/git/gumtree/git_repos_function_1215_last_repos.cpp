static inline int relevant_commit(struct commit *commit)
{
	return (commit->object.flags & (UNINTERESTING | BOTTOM)) != UNINTERESTING;
}