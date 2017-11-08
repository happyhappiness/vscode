int io_flush(int flush_it_all)
{
	int flushed_something = 0;

	if (no_flush)
		return 0;

	if (iobuf_out_cnt) {
		if (io_multiplexing_out)
			mplex_write(sock_f_out, MSG_DATA, iobuf_out, iobuf_out_cnt, 0);
		else
			writefd_unbuffered(iobuf_f_out, iobuf_out, iobuf_out_cnt);
		iobuf_out_cnt = 0;
		flushed_something = 1;
	}

	if (flush_it_all && !defer_forwarding_messages && msg_queue.head) {
		msg_flush();
		flushed_something = 1;
	}

	return flushed_something;
}