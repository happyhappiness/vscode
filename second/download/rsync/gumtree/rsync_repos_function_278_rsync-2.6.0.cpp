int do_chmod(const char *path, mode_t mode)
{
	int code;
	if (dry_run) return 0;
	CHECK_RO
	code = chmod(path, mode);
	if ((code != 0) && preserve_perms)
	    return code;
	return 0;
}