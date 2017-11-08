int do_chmod(const char *path, mode_t mode)
{
	int code;
	if (dry_run) return 0;
	RETURN_ERROR_IF_RO_OR_LO;
	if (S_ISLNK(mode)) {
#ifdef HAVE_LCHMOD
		code = lchmod(path, mode & CHMOD_BITS);
#else
		code = 1;
#endif
	} else
		code = chmod(path, mode & CHMOD_BITS);
	if (code != 0 && preserve_perms)
	    return code;
	return 0;
}