int do_rmdir(char *pathname)
{
	if (dry_run) return 0;
	return rmdir(pathname);
}