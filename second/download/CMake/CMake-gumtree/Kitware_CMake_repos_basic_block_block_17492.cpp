{
	struct xar *xar;
	unsigned char *wb;
	uint64_t length;
	int r;

	xar = (struct xar *)a->format_data;

	/* Empty! */
	if (xar->root->children.first == NULL)
		return (ARCHIVE_OK);

	/* Save the length of all file extended attributes and contents. */
	length = xar->temp_offset;

	/* Connect hardlinked files */
	file_connect_hardlink_files(xar);

	/* Make the TOC */
	r = make_toc(a);
	if (r != ARCHIVE_OK)
		return (r);
	/*
	 * Make the xar header on wbuff(write buffer).
	 */
	wb = xar->wbuff;
	xar->wbuff_remaining = sizeof(xar->wbuff);
	archive_be32enc(&wb[0], HEADER_MAGIC);
	archive_be16enc(&wb[4], HEADER_SIZE);
	archive_be16enc(&wb[6], HEADER_VERSION);
	archive_be64enc(&wb[8], xar->toc.length);
	archive_be64enc(&wb[16], xar->toc.size);
	archive_be32enc(&wb[24], xar->toc.a_sum.alg);
	xar->wbuff_remaining -= HEADER_SIZE;

	/*
	 * Write the TOC
	 */
	r = copy_out(a, xar->toc.temp_offset, xar->toc.length);
	if (r != ARCHIVE_OK)
		return (r);

	/* Write the checksum value of the TOC. */
	if (xar->toc.a_sum.len) {
		if (xar->wbuff_remaining < xar->toc.a_sum.len) {
			r = flush_wbuff(a);
			if (r != ARCHIVE_OK)
				return (r);
		}
		wb = xar->wbuff + (sizeof(xar->wbuff) - xar->wbuff_remaining);
		memcpy(wb, xar->toc.a_sum.val, xar->toc.a_sum.len);
		xar->wbuff_remaining -= xar->toc.a_sum.len;
	}

	/*
	 * Write all file extended attributes and contents.
	 */
	r = copy_out(a, xar->toc.a_sum.len, length);
	if (r != ARCHIVE_OK)
		return (r);
	r = flush_wbuff(a);
	return (r);
}