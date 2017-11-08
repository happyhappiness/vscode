int do_symlink(char *fname1, char *fname2)
{
	if (dry_run) return 0;
	CHECK_RO
	return symlink(fname1, fname2);
}