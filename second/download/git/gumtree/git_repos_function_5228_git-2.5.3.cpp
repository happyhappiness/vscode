static inline int is_merge(void)
{
	return !access(git_path("MERGE_HEAD"), F_OK);
}