void remove_branch_state(void)
{
	unlink(git_path_cherry_pick_head());
	unlink(git_path_revert_head());
	unlink(git_path_merge_head());
	unlink(git_path_merge_rr());
	unlink(git_path_merge_msg());
	unlink(git_path_merge_mode());
	unlink(git_path_squash_msg());
}