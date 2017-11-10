static int open_or_create_logfile(const char *path, void *cb)
{
	int *fd = cb;

	*fd = open(path, O_APPEND | O_WRONLY | O_CREAT, 0666);
	return (*fd < 0) ? -1 : 0;
}