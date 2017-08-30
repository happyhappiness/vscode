	cleanup_pathname_win(a);
#endif
	/* Skip leading '/'. */
	if (*src == '/')
		separator = *src++;

	/* Scan the pathname one element at a time. */
	for (;;) {
