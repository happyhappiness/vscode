static int make_dir(char *name, int mask)
{
	char newdir [MAXPATHLEN];
	char *p, *d;

	/* copy pathname over, look for last '/' */
	for (p = d = newdir; *name; *d++ = *name++)
		if (*name == '/')
			p = d;
	if (p == newdir)
		return 0;
	*p = 0;

	/* make the new directory, if that fails then make its parent */
	while (do_mkdir (newdir, mask) != 0)
		if ((errno != ENOENT) || !make_dir (newdir, mask))
			return 0;

	return 1;
}