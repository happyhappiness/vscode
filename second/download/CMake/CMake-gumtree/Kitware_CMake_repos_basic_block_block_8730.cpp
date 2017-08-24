{
	char *newptr;

	newptr = realloc(data->path, strlen(path) + 1);
	if (newptr == NULL)
		return (ARCHIVE_FATAL);
	data->path = newptr;
	strcpy(data->path, path);
	return (ARCHIVE_OK);
}