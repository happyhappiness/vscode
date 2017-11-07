static int cascade_filter_fn(struct stream_filter *filter,
			     const char *input, size_t *isize_p,
			     char *output, size_t *osize_p)
{
	struct cascade_filter *cas = (struct cascade_filter *) filter;
	size_t filled = 0;
	size_t sz = *osize_p;
	size_t to_feed, remaining;

	/*
	 * input -- (one) --> buf -- (two) --> output
	 */
	while (filled < sz) {
		remaining = sz - filled;

		/* do we already have something to feed two with? */
		if (cas->ptr < cas->end) {
			to_feed = cas->end - cas->ptr;
			if (stream_filter(cas->two,
					  cas->buf + cas->ptr, &to_feed,
					  output + filled, &remaining))
				return -1;
			cas->ptr += (cas->end - cas->ptr) - to_feed;
			filled = sz - remaining;
			continue;
		}

		/* feed one from upstream and have it emit into our buffer */
		to_feed = input ? *isize_p : 0;
		if (input && !to_feed)
			break;
		remaining = sizeof(cas->buf);
		if (stream_filter(cas->one,
				  input, &to_feed,
				  cas->buf, &remaining))
			return -1;
		cas->end = sizeof(cas->buf) - remaining;
		cas->ptr = 0;
		if (input) {
			size_t fed = *isize_p - to_feed;
			*isize_p -= fed;
			input += fed;
		}

		/* do we know that we drained one completely? */
		if (input || cas->end)
			continue;

		/* tell two to drain; we have nothing more to give it */
		to_feed = 0;
		remaining = sz - filled;
		if (stream_filter(cas->two,
				  NULL, &to_feed,
				  output + filled, &remaining))
			return -1;
		if (remaining == (sz - filled))
			break; /* completely drained two */
		filled = sz - remaining;
	}
	*osize_p -= filled;
	return 0;
}