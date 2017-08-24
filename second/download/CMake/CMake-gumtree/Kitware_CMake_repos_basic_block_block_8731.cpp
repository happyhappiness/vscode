{
	char **newargv;

	if (data->path == NULL)
		return (ARCHIVE_FAILED);

	newargv = realloc(data->argv, (data->argc + 2) * sizeof(char *));
	if (newargv == NULL)
		return (ARCHIVE_FATAL);
	data->argv = newargv;
	data->argv[data->argc] = strdup(arg);
	if (data->argv[data->argc] == NULL)
		return (ARCHIVE_FATAL);
	/* Set the terminator of argv. */
	data->argv[++data->argc] = NULL;
	return (ARCHIVE_OK);
}