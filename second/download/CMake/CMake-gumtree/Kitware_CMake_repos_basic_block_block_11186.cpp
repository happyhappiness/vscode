{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfdata *cfdata;
	const void *d;

	cfdata = cab->entry_cfdata;

	/*
	 * Note: '1' here is a performance optimization.
	 * Recall that the decompression layer returns a count of
	 * available bytes; asking for more than that forces the
	 * decompressor to combine reads by copying data.
	 */
	d = __archive_read_ahead(a, 1, avail);
	if (*avail <= 0) {
		*avail = truncated_error(a);
		return (NULL);
	}
	if (*avail > cfdata->uncompressed_bytes_remaining)
		*avail = cfdata->uncompressed_bytes_remaining;
	cfdata->uncompressed_avail = cfdata->uncompressed_size;
	cfdata->unconsumed = *avail;
	cfdata->sum_ptr = d;
	return (d);
}