static int show_filelist_p(void)
{
	return INFO_GTE(FLIST, 1) && xfer_dirs && !am_server && !inc_recurse;
}