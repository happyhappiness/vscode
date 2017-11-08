int robust_unlink(char *fname)
{
#ifndef ETXTBSY
	return do_unlink(fname);
#else
	static int counter = 1;
	int rc, pos, start;
	char path[MAXPATHLEN];

	rc = do_unlink(fname);
	if ((rc == 0) || (errno != ETXTBSY))
		return rc;

	strlcpy(path, fname, MAXPATHLEN);

	pos = strlen(path);
	while((path[--pos] != '/') && (pos >= 0))
		;
	++pos;
	strlcpy(&path[pos], ".rsync", MAXPATHLEN-pos);
	pos += sizeof(".rsync")-1;

	if (pos > (MAXPATHLEN-MAX_RENAMES_DIGITS-1)) {
		errno = ETXTBSY;
		return -1;
	}

	/* start where the last one left off to reduce chance of clashes */
	start = counter;
	do {
		sprintf(&path[pos], "%03d", counter);
		if (++counter >= MAX_RENAMES)
			counter = 1;
	} while (((rc = access(path, 0)) == 0) && (counter != start));

	if (verbose > 0)
		rprintf(FINFO,"renaming %s to %s because of text busy\n",
					    fname, path);

	/* maybe we should return rename()'s exit status? Nah. */
	if (do_rename(fname, path) != 0) {
		errno = ETXTBSY;
		return -1;
	}
	return 0;
#endif
}