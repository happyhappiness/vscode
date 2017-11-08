void permstring(char *perms, mode_t mode)
{
	static const char *perm_map = "rwxrwxrwx";
	int i;

	strlcpy(perms, "----------", 11);

	for (i = 0; i < 9; i++) {
		if (mode & (1 << i))
			perms[9-i] = perm_map[8-i];
	}

	/* Handle setuid/sticky bits.  You might think the indices are
	 * off by one, but remember there's a type char at the
	 * start.  */
	if (mode & S_ISUID)
		perms[3] = (mode & S_IXUSR) ? 's' : 'S';

	if (mode & S_ISGID)
		perms[6] = (mode & S_IXGRP) ? 's' : 'S';

#ifdef S_ISVTX
	if (mode & S_ISVTX)
		perms[9] = (mode & S_IXOTH) ? 't' : 'T';
#endif

	if (S_ISDIR(mode))
		perms[0] = 'd';
	else if (S_ISLNK(mode))
		perms[0] = 'l';
	else if (S_ISBLK(mode))
		perms[0] = 'b';
	else if (S_ISCHR(mode))
		perms[0] = 'c';
	else if (S_ISSOCK(mode))
		perms[0] = 's';
	else if (S_ISFIFO(mode))
		perms[0] = 'p';
}