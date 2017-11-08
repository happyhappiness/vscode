void maybe_send_keepalive(void)
{
	if (time(NULL) - last_io_out >= allowed_lull) {
		if (!iobuf_out || !iobuf_out_cnt) {
			if (protocol_version < 29)
				return; /* there's nothing we can do */
			if (protocol_version >= 30)
				send_msg(MSG_NOOP, "", 0, 0);
			else {
				write_int(sock_f_out, cur_flist->used);
				write_shortint(sock_f_out, ITEM_IS_NEW);
			}
		}
		if (iobuf_out)
			io_flush(NORMAL_FLUSH);
	}
}