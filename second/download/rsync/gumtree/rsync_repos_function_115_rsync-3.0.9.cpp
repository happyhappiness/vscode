void io_set_filesfrom_fds(int f_in, int f_out)
{
	io_filesfrom_f_in = f_in;
	io_filesfrom_f_out = f_out;
	alloc_xbuf(&ff_buf, 2048);
#ifdef ICONV_OPTION
	if (protect_args)
		alloc_xbuf(&iconv_buf, 1024);
#endif
}