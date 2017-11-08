static int show_filelist_p(void)
{
	return verbose && xfer_dirs && !am_server && !inc_recurse;
}