void io_flush(int flush_it_all)
{
	if (iobuf.out.len > iobuf.out_empty_len) {
		if (flush_it_all) /* FULL_FLUSH: flush everything in the output buffers */
			perform_io(iobuf.out.size - iobuf.out_empty_len, PIO_NEED_OUTROOM);
		else /* NORMAL_FLUSH: flush at least 1 byte */
			perform_io(iobuf.out.size - iobuf.out.len + 1, PIO_NEED_OUTROOM);
	}
	if (iobuf.msg.len)
		perform_io(iobuf.msg.size, PIO_NEED_MSGROOM);
}