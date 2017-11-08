void read_stream_flags(int fd)
{
	int i, flags;

	if (protocol_version < 29)
		flag_ptr[7] = NULL;
	for (i = 0, flags = read_int(fd); flag_ptr[i]; i++) {
		int set = flags & (1 << i) ? 1 : 0;
		if (*flag_ptr[i] != set) {
			if (verbose) {
				rprintf(FINFO,
					"%sing the %s option to match the batchfile.\n",
					set ? "Sett" : "Clear", flag_name[i]);
			}
			*flag_ptr[i] = set;
		}
	}
	if (protocol_version < 29) {
		if (recurse)
			xfer_dirs |= 1;
		else if (xfer_dirs < 2)
			xfer_dirs = 0;
	}
}