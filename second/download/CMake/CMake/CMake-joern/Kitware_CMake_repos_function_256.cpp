static int
checksum_final(struct archive_read *a, const void *a_sum_val,
    size_t a_sum_len, const void *e_sum_val, size_t e_sum_len)
{
	struct xar *xar;
	int r;

	xar = (struct xar *)(a->format->data);
	r = _checksum_final(&(xar->a_sumwrk), a_sum_val, a_sum_len);
	if (r == ARCHIVE_OK)
		r = _checksum_final(&(xar->e_sumwrk), e_sum_val, e_sum_len);
	if (r != ARCHIVE_OK)
		archive_set_error(&(a->archive), ARCHIVE_ERRNO_MISC,
		    "Sumcheck error");
	return (r);
}