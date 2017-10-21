		s1++; s2++;
	}
	
	return (int)*s1 - (int)*s2;
}



/**
 * Determine if a symlink points outside the current directory tree.
 * This is considered "unsafe" because e.g. when mirroring somebody
 * else's machine it might allow them to establish a symlink to
 * /etc/passwd, and then read it through a web server.
 *
 * Null symlinks and absolute symlinks are always unsafe.
 *
 * Basically here we are concerned with symlinks whose target contains
 * "..", because this might cause us to walk back up out of the
 * transferred directory.  We are not allowed to go back up and
 * reenter.
 *
 * @param dest Target of the symlink in question.
 *
 * @param src Top source directory currently applicable.  Basically this
 * is the first parameter to rsync in a simple invocation, but it's
 * modified by flist.c in slightly complex ways.
 *
 * @retval True if unsafe
 * @retval False is unsafe
 *
 * @sa t_unsafe.c
 **/
int unsafe_symlink(const char *dest, const char *src)
{
	const char *name, *slash;
	int depth = 0;

	/* all absolute and null symlinks are unsafe */
	if (!dest || !*dest || *dest == '/') return 1;

	/* find out what our safety margin is */
	for (name = src; (slash = strchr(name, '/')) != 0; name = slash+1) {
		if (strncmp(name, "../", 3) == 0) {
			depth=0;
		} else if (strncmp(name, "./", 2) == 0) {
			/* nothing */
		} else {
			depth++;
		}
	}
	if (strcmp(name, "..") == 0)
		depth = 0;

	for (name = dest; (slash = strchr(name, '/')) != 0; name = slash+1) {
		if (strncmp(name, "../", 3) == 0) {
			/* if at any point we go outside the current directory
			   then stop - it is unsafe */
			if (--depth < 0)
				return 1;
		} else if (strncmp(name, "./", 2) == 0) {
			/* nothing */
		} else {
			depth++;
		}
	}
	if (strcmp(name, "..") == 0)
		depth--;

	return (depth < 0);
}


/**
 * Return the date and time as a string
 **/
char *timestring(time_t t)
{
	static char TimeBuf[200];
	struct tm *tm = localtime(&t);

#ifdef HAVE_STRFTIME
