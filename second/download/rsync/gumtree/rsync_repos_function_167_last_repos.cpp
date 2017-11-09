void read_buf(int f, char *buf, size_t len)
{
	if (f != iobuf.in_fd) {
		if (safe_read(f, buf, len) != len)
			whine_about_eof(False); /* Doesn't return. */
		goto batch_copy;
	}

	if (!IN_MULTIPLEXED) {
		raw_read_buf(buf, len);
		total_data_read += len;
		if (forward_flist_data)
			write_buf(iobuf.out_fd, buf, len);
	  batch_copy:
		if (f == write_batch_monitor_in)
			safe_write(batch_fd, buf, len);
		return;
	}

	while (1) {
		size_t siz;

		while (!iobuf.raw_input_ends_before)
			read_a_msg();

		siz = MIN(len, iobuf.raw_input_ends_before - iobuf.in.pos);
		if (siz >= iobuf.in.size)
			siz = iobuf.in.size;
		raw_read_buf(buf, siz);
		total_data_read += siz;

		if (forward_flist_data)
			write_buf(iobuf.out_fd, buf, siz);

		if (f == write_batch_monitor_in)
			safe_write(batch_fd, buf, siz);

		if ((len -= siz) == 0)
			break;
		buf += siz;
	}
}