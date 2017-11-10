static int null_filter_fn(struct stream_filter *filter,
			  const char *input, size_t *isize_p,
			  char *output, size_t *osize_p)
{
	size_t count;

	if (!input)
		return 0; /* we do not keep any states */
	count = *isize_p;
	if (*osize_p < count)
		count = *osize_p;
	if (count) {
		memmove(output, input, count);
		*isize_p -= count;
		*osize_p -= count;
	}
	return 0;
}