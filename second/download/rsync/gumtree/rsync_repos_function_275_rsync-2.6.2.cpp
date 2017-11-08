int do_symlink(char *fname1, char *fname2)
{
	if (dry_run) return 0;
	RETURN_ERROR_IF_RO_OR_LO;
	return symlink(fname1, fname2);
}