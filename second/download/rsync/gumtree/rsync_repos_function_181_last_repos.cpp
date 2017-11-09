void write_buf(int f, const char *buf, size_t len)
{
	size_t pos, siz;

	if (f != iobuf.out_fd) {
		safe_write(f, buf, len);
		goto batch_copy;
	}

	if (iobuf.out.len + len > iobuf.out.size)
		perform_io(len, PIO_NEED_OUTROOM);

	pos = iobuf.out.pos + iobuf.out.len; /* Must be set after any flushing. */
	if (pos >= iobuf.out.size)
		pos -= iobuf.out.size;

	/* Handle a split copy if we wrap around the end of the circular buffer. */
	if (pos >= iobuf.out.pos && (siz = iobuf.out.size - pos) < len) {
		memcpy(iobuf.out.buf + pos, buf, siz);
		memcpy(iobuf.out.buf, buf + siz, len - siz);
	} else
		memcpy(iobuf.out.buf + pos, buf, len);

	iobuf.out.len += len;
	total_data_written += len;

  batch_copy:
	if (f == write_batch_monitor_out)
		safe_write(batch_fd, buf, len);
}