
	/* if protocol version is >= 17 then send the io_error flag */
	if (f != -1 && remote_version >= 17) {
		write_int(f, io_error);
	}

	return flist;
}


struct file_list *recv_file_list(int f)
{
