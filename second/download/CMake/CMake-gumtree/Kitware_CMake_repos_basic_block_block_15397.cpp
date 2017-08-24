{
	struct _7zip *zip;
	int r;

	zip = (struct _7zip *)a->format_data;
	if (zip->temp_offset > 0 &&
	    lseek(zip->temp_fd, offset, SEEK_SET) < 0) {
		archive_set_error(&(a->archive), errno, "lseek failed");
		return (ARCHIVE_FATAL);
	}
	while (length) {
		size_t rsize;
		ssize_t rs;
		unsigned char *wb;

		if (length > zip->wbuff_remaining)
			rsize = zip->wbuff_remaining;
		else
			rsize = (size_t)length;
		wb = zip->wbuff + (sizeof(zip->wbuff) - zip->wbuff_remaining);
		rs = read(zip->temp_fd, wb, rsize);
		if (rs < 0) {
			archive_set_error(&(a->archive), errno,
			    "Can't read temporary file(%jd)",
			    (intmax_t)rs);
			return (ARCHIVE_FATAL);
		}
		if (rs == 0) {
			archive_set_error(&(a->archive), 0,
			    "Truncated 7-Zip archive");
			return (ARCHIVE_FATAL);
		}
		zip->wbuff_remaining -= rs;
		length -= rs;
		if (zip->wbuff_remaining == 0) {
			r = flush_wbuff(a);
			if (r != ARCHIVE_OK)
				return (r);
		}
	}
	return (ARCHIVE_OK);
}