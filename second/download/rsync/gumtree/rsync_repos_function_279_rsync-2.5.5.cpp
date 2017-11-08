static int show_filelist_p(void)
{
	return verbose && recurse && !am_server;
}