struct userdiff_driver *get_textconv(struct diff_filespec *one)
{
	if (!DIFF_FILE_VALID(one))
		return NULL;

	diff_filespec_load_driver(one);
	return userdiff_get_textconv(one->driver);
}