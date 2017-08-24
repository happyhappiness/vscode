{
	wchar_t *slash;
	int r;

	/* Remove tail element to obtain parent name. */
	slash = wcsrchr(path, L'\\');
	if (slash == NULL)
		return (ARCHIVE_OK);
	*slash = L'\0';
	r = create_dir(a, path);
	*slash = L'\\';
	return (r);
}