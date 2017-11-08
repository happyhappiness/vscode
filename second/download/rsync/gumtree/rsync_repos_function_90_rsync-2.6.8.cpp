void io_set_filesfrom_fds(int f_in, int f_out)
{
	io_filesfrom_f_in = f_in;
	io_filesfrom_f_out = f_out;
	io_filesfrom_bp = io_filesfrom_buf;
	io_filesfrom_lastchar = '\0';
	io_filesfrom_buflen = 0;
}