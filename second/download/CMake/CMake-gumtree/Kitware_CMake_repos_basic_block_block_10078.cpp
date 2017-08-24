{
	struct read_FILE_data *mine = (struct read_FILE_data *)client_data;
#if HAVE_FSEEKO
	off_t skip = (off_t)request;
#elif HAVE__FSEEKI64
	int64_t skip = request;
#else
	long skip = (long)request;
#endif
	int skip_bits = sizeof(skip) * 8 - 1;

	(void)a; /* UNUSED */

	/*
	 * If we can't skip, return 0 as the amount we did step and
	 * the caller will work around by reading and discarding.
	 */
	if (!mine->can_skip)
		return (0);
	if (request == 0)
		return (0);

	/* If request is too big for a long or an off_t, reduce it. */
	if (sizeof(request) > sizeof(skip)) {
		int64_t max_skip =
		    (((int64_t)1 << (skip_bits - 1)) - 1) * 2 + 1;
		if (request > max_skip)
			skip = max_skip;
	}

#ifdef __ANDROID__
        /* fileno() isn't safe on all platforms ... see above. */
	if (lseek(fileno(mine->f), skip, SEEK_CUR) < 0)
#elif HAVE_FSEEKO
	if (fseeko(mine->f, skip, SEEK_CUR) != 0)
#elif HAVE__FSEEKI64
	if (_fseeki64(mine->f, skip, SEEK_CUR) != 0)
#else
	if (fseek(mine->f, skip, SEEK_CUR) != 0)
#endif
	{
		mine->can_skip = 0;
		return (0);
	}
	return (request);
}