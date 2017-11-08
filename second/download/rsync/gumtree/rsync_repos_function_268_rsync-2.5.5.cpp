int do_chmod(const char *path, mode_t mode)
{
	if (dry_run) return 0;
	CHECK_RO
	return chmod(path, mode);
}