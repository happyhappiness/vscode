void write_stream_flags(int fd)
{
	int i, flags;

	tweaked_append = append_mode == 1;
	tweaked_append_verify = append_mode == 2;
#ifdef ICONV_OPTION
	tweaked_iconv = iconv_opt != NULL;
#endif

	/* Start the batch file with a bitmap of data-stream-affecting
	 * flags. */
	for (i = 0, flags = 0; flag_ptr[i]; i++) {
		if (*flag_ptr[i])
			flags |= 1 << i;
	}
	write_int(fd, flags);
}