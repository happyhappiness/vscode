static char *
build_gnu_sparse_name(char *dest, const char *src)
{
	char buff[64];
	const char *p;

	/* Handle the null filename case. */
	if (src == NULL || *src == '\0') {
		strcpy(dest, "GNUSparseFile/blank");
		return (dest);
	}

	/* Prune final '/' and other unwanted final elements. */
	p = src + strlen(src);
	for (;;) {
		/* Ends in "/", remove the '/' */
		if (p > src && p[-1] == '/') {
			--p;
			continue;
		}
		/* Ends in "/.", remove the '.' */
		if (p > src + 1 && p[-1] == '.'
		    && p[-2] == '/') {
			--p;
			continue;
		}
		break;
	}

#if HAVE_GETPID && 0  /* Disable this as pax attribute name. */
	sprintf(buff, "GNUSparseFile.%d", getpid());
#else
	/* If the platform can't fetch the pid, don't include it. */
	strcpy(buff, "GNUSparseFile");
#endif
	/* General case: build a ustar-compatible name adding
	 * "/GNUSparseFile/". */
	build_ustar_entry_name(dest, src, p - src, buff);

	return (dest);
}