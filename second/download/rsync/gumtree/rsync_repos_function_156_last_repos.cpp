void maybe_send_keepalive(time_t now, int flags)
{
	if (flags & MSK_ACTIVE_RECEIVER)
		last_io_in = now; /* Fudge things when we're working hard on the files. */

	/* Early in the transfer (before the receiver forks) the receiving side doesn't
	 * care if it hasn't sent data in a while as long as it is receiving data (in
	 * fact, a pre-3.1.0 rsync would die if we tried to send it a keep alive during
	 * this time).  So, if we're an early-receiving proc, just return and let the
	 * incoming data determine if we timeout. */
	if (!am_sender && !am_receiver && !am_generator)
		return;

	if (now - last_io_out >= allowed_lull) {
		/* The receiver is special:  it only sends keep-alive messages if it is
		 * actively receiving data.  Otherwise, it lets the generator timeout. */
		if (am_receiver && now - last_io_in >= io_timeout)
			return;

		if (!iobuf.msg.len && iobuf.out.len == iobuf.out_empty_len)
			send_msg(MSG_DATA, "", 0, 0);
		if (!(flags & MSK_ALLOW_FLUSH)) {
			/* Let the caller worry about writing out the data. */
		} else if (iobuf.msg.len)
			perform_io(iobuf.msg.size - iobuf.msg.len + 1, PIO_NEED_MSGROOM);
		else if (iobuf.out.len > iobuf.out_empty_len)
			io_flush(NORMAL_FLUSH);
	}
}