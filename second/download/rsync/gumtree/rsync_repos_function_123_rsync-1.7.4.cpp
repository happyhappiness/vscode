int do_mkdir(char *fname, mode_t mode)
{
	if (dry_run) return 0;
	return mkdir(fname, mode);
}