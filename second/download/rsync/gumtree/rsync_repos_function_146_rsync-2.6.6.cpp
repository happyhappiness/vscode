void write_stream_flags(int fd)
{
	int i, flags;

	/* Start the batch file with a bitmap of data-stream-affecting
	 * flags. */
	if (protocol_version < 29)
		flag_ptr[7] = NULL;
	for (i = 0, flags = 0; flag_ptr[i]; i++) {
		if (*flag_ptr[i])
			flags |= 1 << i;
	}
	write_int(fd, flags);
}