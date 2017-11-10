static int show_file(const char *arg, int output_prefix)
{
	show_default();
	if ((filter & (DO_NONFLAGS|DO_NOREV)) == (DO_NONFLAGS|DO_NOREV)) {
		if (output_prefix) {
			const char *prefix = startup_info->prefix;
			show(prefix_filename(prefix,
					     prefix ? strlen(prefix) : 0,
					     arg));
		} else
			show(arg);
		return 1;
	}
	return 0;
}