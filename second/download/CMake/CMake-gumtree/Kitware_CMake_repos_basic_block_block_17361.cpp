{
	struct xar *xar;
	struct file *file;
	size_t s;
	ssize_t w;

	xar = (struct xar *)a->format_data;
	if (xar->cur_file == NULL)
		return (ARCHIVE_OK);

	while (xar->bytes_remaining > 0) {
		s = (size_t)xar->bytes_remaining;
		if (s > a->null_length)
			s = a->null_length;
		w = xar_write_data(a, a->nulls, s);
		if (w > 0)
			xar->bytes_remaining -= w;
		else
			return (w);
	}
	file = xar->cur_file;
	checksum_final(&(xar->e_sumwrk), &(file->data.e_sum));
	checksum_final(&(xar->a_sumwrk), &(file->data.a_sum));
	xar->cur_file = NULL;

	return (ARCHIVE_OK);
}