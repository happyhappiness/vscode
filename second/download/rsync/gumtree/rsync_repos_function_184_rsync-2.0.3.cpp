int do_rename(char *fname1, char *fname2)
{
	if (dry_run) return 0;
	CHECK_RO
	return rename(fname1, fname2);
}