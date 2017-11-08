int do_mkdir(char *fname, mode_t mode)
{
	if (dry_run)
		return 0;
	CHECK_RO;
	trim_trailing_slashes(fname);	
	return mkdir(fname, mode);
}