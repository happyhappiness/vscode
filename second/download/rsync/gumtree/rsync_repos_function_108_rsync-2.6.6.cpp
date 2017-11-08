void io_flush(int flush_it_all)
{
	msg_list_push(flush_it_all);

	if (!iobuf_out_cnt || no_flush)
		return;

	if (io_multiplexing_out)
		mplex_write(MSG_DATA, iobuf_out, iobuf_out_cnt);
	else
		writefd_unbuffered(sock_f_out, iobuf_out, iobuf_out_cnt);
	iobuf_out_cnt = 0;
}