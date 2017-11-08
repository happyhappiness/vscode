static void list_file (const char *fname)
{
	STRUCT_STAT buf;
	char permbuf[PERMSTRING_SIZE];
	struct tm *mt;
	char datebuf[50];
	char linkbuf[4096];

	if (do_lstat(fname, &buf) == -1)
		failed ("stat", fname);

	/* The size of anything but a regular file is probably not
	 * worth thinking about. */
	if (!S_ISREG(buf.st_mode))
		buf.st_size = 0;

	/* On some BSD platforms the mode bits of a symlink are
	 * undefined.  Also it tends not to be possible to reset a
	 * symlink's mtime, so we have to ignore it too. */
	if (S_ISLNK(buf.st_mode)) {
		int len;
		buf.st_mode &= ~0777;
		buf.st_mtime = (time_t)0;
		buf.st_uid = buf.st_gid = 0;
		strcpy(linkbuf, " -> ");
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
		
		sprintf(datebuf, "%04d-%02d-%02d %02d:%02d:%02d",
			mt->tm_year + 1900,
			mt->tm_mon + 1,
			mt->tm_mday,
			mt->tm_hour,
			mt->tm_min,
			mt->tm_sec);
	} else {
		strcpy(datebuf, "                   ");
	}
	
	/* TODO: Perhaps escape special characters in fname? */
	
	
	/* NB: need to pass size as a double because it might be be
	 * too large for a long. */
	printf("%s %12.0f %6d.%-6d %6d %s %s%s\n",
	       permbuf, (double) buf.st_size,
	       buf.st_uid, buf.st_gid,
	       buf.st_nlink,
	       datebuf, fname, linkbuf);
}