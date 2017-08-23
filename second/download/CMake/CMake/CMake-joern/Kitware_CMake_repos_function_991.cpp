static int
copy_out(struct archive_write *a, uint64_t offset, uint64_t length)
{
	struct xar *xar;
	int r;

	xar = (struct xar *)a->format_data;
	if (lseek(xar->temp_fd, offset, SEEK_SET) < 0) {
		archive_set_error(&(a->archive), errno, "lseek failed");
		return (ARCHIVE_FATAL);
	}
	while (length) {
		size_t rsize;
		ssize_t rs;
		unsigned char *wb;

		if (length > xar->wbuff_remaining)
			rsize = xar->wbuff_remaining;
		else
			rsize = (size_t)length;
		wb = xar->wbuff + (sizeof(xar->wbuff) - xar->wbuff_remaining);
		rs = read(xar->temp_fd, wb, rsize);
		if (rs < 0) {
			archive_set_error(&(a->archive), errno,
			    "Can't read temporary file(%jd)",
			    (intmax_t)rs);
			return (ARCHIVE_FATAL);
		}
		if (rs == 0) {
			archive_set_error(&(a->archive), 0,
			    "Truncated xar archive");
			return (ARCHIVE_FATAL);
		}
		xar->wbuff_remaining -= rs;
		length -= rs;
		if (xar->wbuff_remaining == 0) {
			r = flush_wbuff(a);
			if (r != ARCHIVE_OK)
				return (r);
		}
	}
	return (ARCHIVE_OK);
}