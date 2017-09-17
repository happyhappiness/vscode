#endif

    ap_soft_timeout("send body", r);

    FD_ZERO(&fds);
    while (!r->connection->aborted) {
        if ((length > 0) && (total_bytes_sent + IOBUFSIZE) > length)
            len = length - total_bytes_sent;
        else
            len = IOBUFSIZE;

        do {
            n = ap_bread(fb, buf, len);
            if (n >= 0 || r->connection->aborted)
                break;
            if (n < 0 && errno != EAGAIN)
                break;
            /* we need to block, so flush the output first */
            ap_bflush(r->connection->client);
            if (r->connection->aborted)
