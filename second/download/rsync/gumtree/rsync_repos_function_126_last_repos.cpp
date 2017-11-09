static void check_timeout(BOOL allow_keepalive, int keepalive_flags)
{
	time_t t, chk;

	/* On the receiving side, the generator is now the one that decides
	 * when a timeout has occurred.  When it is sifting through a lot of
	 * files looking for work, it will be sending keep-alive messages to
	 * the sender, and even though the receiver won't be sending/receiving
	 * anything (not even keep-alive messages), the successful writes to
	 * the sender will keep things going.  If the receiver is actively
	 * receiving data, it will ensure that the generator knows that it is
	 * not idle by sending the generator keep-alive messages (since the
	 * generator might be blocked trying to send checksums, it needs to
	 * know that the receiver is active).  Thus, as long as one or the
	 * other is successfully doing work, the generator will not timeout. */
	if (!io_timeout)
		return;

	t = time(NULL);

	if (allow_keepalive) {
		/* This may put data into iobuf.msg w/o flushing. */
		maybe_send_keepalive(t, keepalive_flags);
	}

	if (!last_io_in)
		last_io_in = t;

	if (am_receiver)
		return;

	chk = MAX(last_io_out, last_io_in);
	if (t - chk >= io_timeout) {
		if (am_server)
			msgs2stderr = 1;
		rprintf(FERROR, "[%s] io timeout after %d seconds -- exiting\n",
			who_am_i(), (int)(t-chk));
		exit_cleanup(RERR_TIMEOUT);
	}
}