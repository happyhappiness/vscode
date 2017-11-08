void write_stream_flags(int fd)
{
	int i, flags;

#if Z_DEFAULT_COMPRESSION == -1
	tweaked_compress_level = do_compression ? def_compress_level + 2 : 0;
#else
#error internal logic error!  Fix def_compress_level logic above and below too!
#endif

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