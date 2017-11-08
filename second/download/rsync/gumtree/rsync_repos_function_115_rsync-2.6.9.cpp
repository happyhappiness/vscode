void io_flush(int flush_it_all)
{
	msg2genr_flush(flush_it_all);
	msg2sndr_flush();

	if (!iobuf_out_cnt || no_flush)
		return;

	if (io_multiplexing_out)
		mplex_write(MSG_DATA, iobuf_out, iobuf_out_cnt);
	else
		writefd_unbuffered(sock_f_out, iobuf_out, iobuf_out_cnt);
	iobuf_out_cnt = 0;
}