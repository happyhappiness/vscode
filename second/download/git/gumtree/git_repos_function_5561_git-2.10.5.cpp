static inline int is_merge(void)
{
	return !access(git_path_merge_head(), F_OK);
}