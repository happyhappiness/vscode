int do_unlink(char *fname)
{
	if (dry_run) return 0;
	return unlink(fname);
}