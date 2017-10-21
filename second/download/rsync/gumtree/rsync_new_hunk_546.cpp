#ifdef HAVE_ST_RDEV
	file->rdev = st.st_rdev;
#endif

#if SUPPORT_LINKS
	if (S_ISLNK(st.st_mode)) {
		file->link = strdup(linkbuf);
	}
#endif

	if (always_checksum) {
		file->sum = (char *)malloc(MD4_SUM_LENGTH);
		if (!file->sum) out_of_memory("md4 sum");
