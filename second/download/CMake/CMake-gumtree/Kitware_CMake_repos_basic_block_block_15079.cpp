{
	int h;
	struct bucket *b;
	struct bucket *ucache = (struct bucket *)private_data;

	/* If no uname, just use the uid provided. */
	if (uname == NULL || *uname == '\0')
		return (uid);

	/* Try to find uname in the cache. */
	h = hash(uname);
	b = &ucache[h % cache_size ];
	if (b->name != NULL && b->hash == h && strcmp(uname, b->name) == 0)
		return ((uid_t)b->id);

	/* Free the cache slot for a new entry. */
	if (b->name != NULL)
		free(b->name);
	b->name = strdup(uname);
	/* Note: If strdup fails, that's okay; we just won't cache. */
	b->hash = h;
#if HAVE_PWD_H
#  if HAVE_GETPWNAM_R
	{
		char _buffer[128];
		size_t bufsize = 128;
		char *buffer = _buffer;
		char *allocated = NULL;
		struct passwd	pwent, *result;
		int r;

		for (;;) {
			result = &pwent; /* Old getpwnam_r ignores last arg. */
			r = getpwnam_r(uname, &pwent, buffer, bufsize, &result);
			if (r == 0)
				break;
			if (r != ERANGE)
				break;
			bufsize *= 2;
			free(allocated);
			allocated = malloc(bufsize);
			if (allocated == NULL)
				break;
			buffer = allocated;
		}
		if (result != NULL)
			uid = result->pw_uid;
		free(allocated);
	}
#  else /* HAVE_GETPWNAM_R */
	{
		struct passwd *result;

		result = getpwnam(uname);
		if (result != NULL)
			uid = result->pw_uid;
	}
#endif	/* HAVE_GETPWNAM_R */
#elif defined(_WIN32) && !defined(__CYGWIN__)
	/* TODO: do a uname->uid lookup for Windows. */
#else
	#error No way to look up uids on this platform
#endif
	b->id = (uid_t)uid;

	return (uid);
}