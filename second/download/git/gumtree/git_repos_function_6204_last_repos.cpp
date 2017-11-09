static void drop_save(void)
{
	unlink(git_path_merge_head());
	unlink(git_path_merge_msg());
	unlink(git_path_merge_mode());
}