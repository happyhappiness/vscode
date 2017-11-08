int do_rmdir(char *pathname)
{
	if (dry_run) return 0;
	CHECK_RO
	return rmdir(pathname);
}