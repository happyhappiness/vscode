static int skip_filesystem(char *fname, STRUCT_STAT * st)
{
	STRUCT_STAT st2;
	char *p = strrchr(fname, '/');

	/* skip all but directories */
	if (!S_ISDIR(st->st_mode))
		return 1;

	/* if its not a subdirectory then allow */
	if (!p)
		return 0;

	*p = 0;
	if (link_stat(fname, &st2)) {
		*p = '/';
		return 0;
	}
	*p = '/';

	return (st2.st_dev != filesystem_dev);
}