size_t fill_textconv(struct userdiff_driver *driver,
		     struct diff_filespec *df,
		     char **outbuf)
{
	size_t size;

	if (!driver || !driver->textconv) {
		if (!DIFF_FILE_VALID(df)) {
			*outbuf = "";
			return 0;
		}
		if (diff_populate_filespec(df, 0))
			die("unable to read files to diff");
		*outbuf = df->data;
		return df->size;
	}

	if (driver->textconv_cache && df->sha1_valid) {
		*outbuf = notes_cache_get(driver->textconv_cache, df->sha1,
					  &size);
		if (*outbuf)
			return size;
	}
