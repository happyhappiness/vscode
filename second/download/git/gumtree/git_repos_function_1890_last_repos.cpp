static int validate_remote_tracking_branch(char *ref)
{
	return !for_each_remote(check_tracking_branch, ref);
}