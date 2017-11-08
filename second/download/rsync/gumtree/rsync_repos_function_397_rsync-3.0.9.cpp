int get_tmpname(char *fnametmp, const char *fname)
{
	int maxname, added, length = 0;
	const char *f;
	char *suf;

	if (tmpdir) {
		/* Note: this can't overflow, so the return value is safe */
		length = strlcpy(fnametmp, tmpdir, MAXPATHLEN - 2);
		fnametmp[length++] = '/';
	}

	if ((f = strrchr(fname, '/')) != NULL) {
		++f;
		if (!tmpdir) {
			length = f - fname;
			/* copy up to and including the slash */
			strlcpy(fnametmp, fname, length + 1);
		}
	} else
		f = fname;
	fnametmp[length++] = '.';

	/* The maxname value is bufsize, and includes space for the '\0'.
	 * NAME_MAX needs an extra -1 for the name's leading dot. */
	maxname = MIN(MAXPATHLEN - length - TMPNAME_SUFFIX_LEN,
		      NAME_MAX - 1 - TMPNAME_SUFFIX_LEN);

	if (maxname < 1) {
		rprintf(FERROR_XFER, "temporary filename too long: %s\n", fname);
		fnametmp[0] = '\0';
		return 0;
	}

	added = strlcpy(fnametmp + length, f, maxname);
	if (added >= maxname)
		added = maxname - 1;
	suf = fnametmp + length + added;

	/* Trim any dangling high-bit chars if the first-trimmed char (if any) is
	 * also a high-bit char, just in case we cut into a multi-byte sequence.
	 * We are guaranteed to stop because of the leading '.' we added. */
	if ((int)f[added] & 0x80) {
		while ((int)suf[-1] & 0x80)
			suf--;
	}

	memcpy(suf, TMPNAME_SUFFIX, TMPNAME_SUFFIX_LEN+1);

	return 1;
}