#endif

    ap_soft_timeout("send body", r);

    FD_ZERO(&fds);
    while (!r->connection->aborted) {
#ifdef NDELAY_PIPE_RETURNS_ZERO
	/* Contributed by dwd@bell-labs.com for UTS 2.1.2, where the fcntl */
	/*   O_NDELAY flag causes read to return 0 when there's nothing */
	/*   available when reading from a pipe.  That makes it tricky */
	/*   to detect end-of-file :-(.  This stupid bug is even documented */
	/*   in the read(2) man page where it says that everything but */
	/*   pipes return -1 and EAGAIN.  That makes it a feature, right? */
	int afterselect = 0;
#endif
        if ((length > 0) && (total_bytes_sent + IOBUFSIZE) > length)
            len = length - total_bytes_sent;
        else
            len = IOBUFSIZE;

        do {
            n = ap_bread(fb, buf, len);
#ifdef NDELAY_PIPE_RETURNS_ZERO
	    if ((n > 0) || (n == 0 && afterselect))
		break;
#else
            if (n >= 0)
                break;
#endif
            if (r->connection->aborted)
                break;
            if (n < 0 && errno != EAGAIN)
                break;
            /* we need to block, so flush the output first */
            ap_bflush(r->connection->client);
            if (r->connection->aborted)
