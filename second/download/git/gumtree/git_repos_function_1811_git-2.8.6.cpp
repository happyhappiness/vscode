void reprepare_packed_git(void)
{
	prepare_packed_git_run_once = 0;
	prepare_packed_git();
}