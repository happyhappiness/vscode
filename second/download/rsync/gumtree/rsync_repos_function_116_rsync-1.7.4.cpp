int do_link(char *fname1, char *fname2)
{
	if (dry_run) return 0;
	return link(fname1, fname2);
}