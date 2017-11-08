static int show_filelist_p(void)
{
	return verbose && (recurse || files_from) && !am_server;
}