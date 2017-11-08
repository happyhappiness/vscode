static void list_file(const char *fname)
{
	STRUCT_STAT buf;
	char permbuf[PERMSTRING_SIZE];
	struct tm *mt;
	char datebuf[50];
	char linkbuf[4096];

	if (do_lstat(fname, &buf) < 0)
		failed("stat", fname);
#ifdef SUPPORT_XATTRS
	if (am_root < 0)
		stat_xattr(fname, &buf);
#endif

	/* The size of anything but a regular file is probably not
	 * worth thinking about. */
	if (!S_ISREG(buf.st_mode))
		buf.st_size = 0;

	/* On some BSD platforms the mode bits of a symlink are
	 * undefined.  Also it tends not to be possible to reset a
	 * symlink's mtime, so we default to ignoring it too. */
	if (S_ISLNK(buf.st_mode)) {
		int len;
		buf.st_mode &= ~0777;
		if (!link_times)
			buf.st_mtime = (time_t)0;
		if (!link_owner)
			buf.st_uid = buf.st_gid = 0;
		strlcpy(linkbuf, " -> ", sizeof linkbuf);
		/* const-cast required for silly UNICOS headers */
		len = readlink((char *) fname, linkbuf+4, sizeof(linkbuf) - 4);
		if (len == -1)
			failed("readlink", fname);
		else
			/* it's not nul-terminated */
			linkbuf[4+len] = 0;
	} else {
		linkbuf[0] = 0;
	}

	permstring(permbuf, buf.st_mode);

	if (buf.st_mtime) {
		mt = gmtime(&buf.st_mtime);

		snprintf(datebuf, sizeof datebuf,
			"%04d-%02d-%02d %02d:%02d:%02d",
			(int)mt->tm_year + 1900,
			(int)mt->tm_mon + 1,
			(int)mt->tm_mday,
			(int)mt->tm_hour,
			(int)mt->tm_min,
			(int)mt->tm_sec);
	} else
		strlcpy(datebuf, "                   ", sizeof datebuf);

	/* TODO: Perhaps escape special characters in fname? */

	printf("%s ", permbuf);
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
		printf("%5ld,%6ld",
		    (long)major(buf.st_rdev),
		    (long)minor(buf.st_rdev));
	} else /* NB: use double for size since it might not fit in a long. */
		printf("%12.0f", (double)buf.st_size);
	printf(" %6ld.%-6ld %6ld %s %s%s\n",
	       (long)buf.st_uid, (long)buf.st_gid, (long)buf.st_nlink,
	       datebuf, fname, linkbuf);
}