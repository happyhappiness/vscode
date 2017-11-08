void reprepare_packed_git(void)
{
	approximate_object_count_valid = 0;
	prepare_packed_git_run_once = 0;
	prepare_packed_git();
}