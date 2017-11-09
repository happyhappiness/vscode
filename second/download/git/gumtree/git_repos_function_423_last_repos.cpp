static inline int parse_commit(struct commit *item)
{
	return parse_commit_gently(item, 0);
}