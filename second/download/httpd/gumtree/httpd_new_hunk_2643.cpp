#endif

    /* Since we are reading from one buffer and writing to another,
     * it is unsafe to do a soft_timeout here, at least until the proxy
     * has its own timeout handler which can set both buffers to EOUT.
     */

    ap_kill_timeout(r);

#ifdef WIN32
    /* works fine under win32, so leave it */
    ap_hard_timeout("proxy send body", r);
    alt_to = 0;
#else
    /* CHECKME! Since hard_timeout won't work in unix on sends with partial
     * cache completion, we have to alternate between hard_timeout
     * for reads, and soft_timeout for send.  This is because we need
     * to get a return from ap_bwrite to be able to continue caching.
     * BUT, if we *can't* continue anyway, just use hard_timeout.
     */

    if (c) {
        if (c->len <= 0 || c->cache_completion == 1) {
            ap_hard_timeout("proxy send body", r);
            alt_to = 0;
        }
    } else {
        ap_hard_timeout("proxy send body", r);
        alt_to = 0;
    }
#endif

    while (ok && f != NULL) {
        if (alt_to)
            ap_hard_timeout("proxy send body", r);

	n = ap_bread(f, buf, IOBUFSIZE);

        if (alt_to)
            ap_kill_timeout(r);
        else
            ap_reset_timeout(r);

	if (n == -1) {		/* input error */
	    if (f2 != NULL)
		f2 = ap_proxy_cache_error(c);
	    break;
	}
	if (n == 0)
	    break;		/* EOF */
	o = 0;
	total_bytes_rcv += n;

        if (f2 != NULL) {
            if (ap_bwrite(f2, &buf[0], n) != n) {
		f2 = ap_proxy_cache_error(c);
            } else {
                c->written += n;
            }
        }

	while (n && !con->aborted) {
            if (alt_to)
                ap_soft_timeout("proxy send body", r);

	    w = ap_bwrite(con->client, &buf[o], n);

            if (alt_to)
                ap_kill_timeout(r);
            else
                ap_reset_timeout(r);

	    if (w <= 0) {
		if (f2 != NULL) {
                    /* when a send failure occurs, we need to decide
                     * whether to continue loading and caching the
                     * document, or to abort the whole thing
                     */
                    ok = (c->len > 0) &&
                         (c->cache_completion > 0) &&
                         (c->len * c->cache_completion < total_bytes_rcv);

                    if (! ok) {
                        ap_pclosef(c->req->pool, c->fp->fd);
                        c->fp = NULL;
                        f2 = NULL;
                        unlink(c->tempfile);
                    }
		}
                con->aborted = 1;
		break;
	    }
	    n -= w;
	    o += w;
	}
    }

    if (!con->aborted)
	ap_bflush(con->client);

    ap_kill_timeout(r);
    return total_bytes_rcv;
}

/*
 * Read a header from the array, returning the first entry
 */
struct hdr_entry *
