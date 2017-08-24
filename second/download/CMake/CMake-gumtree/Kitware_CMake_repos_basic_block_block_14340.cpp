{
	if (f->open == NULL)
		return (ARCHIVE_OK);
	return (f->open)(f);
}