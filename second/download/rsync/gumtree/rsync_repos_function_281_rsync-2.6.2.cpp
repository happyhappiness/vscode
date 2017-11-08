int do_chmod(const char *path, mode_t mode)
{
	int code;
	if (dry_run) return 0;
	RETURN_ERROR_IF_RO_OR_LO;
	code = chmod(path, mode);
	if (code != 0 && preserve_perms)
	    return code;
	return 0;
}