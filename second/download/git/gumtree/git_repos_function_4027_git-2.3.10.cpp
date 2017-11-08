int textconv_object(const char *path,
		    unsigned mode,
		    const unsigned char *sha1,
		    int sha1_valid,
		    char **buf,
		    unsigned long *buf_size)
{
	struct diff_filespec *df;
	struct userdiff_driver *textconv;

	df = alloc_filespec(path);
	fill_filespec(df, sha1, sha1_valid, mode);
	textconv = get_textconv(df);
	if (!textconv) {
		free_filespec(df);
		return 0;
	}

	*buf_size = fill_textconv(textconv, df, buf);
	free_filespec(df);
	return 1;
}