static int show_file(const char *arg, int output_prefix)
{
	show_default();
	if ((filter & (DO_NONFLAGS|DO_NOREV)) == (DO_NONFLAGS|DO_NOREV)) {
		if (output_prefix) {
			const char *prefix = startup_info->prefix;
			char *fname = prefix_filename(prefix, arg);
			show(fname);
			free(fname);
		} else
			show(arg);
		return 1;
	}
	return 0;
}