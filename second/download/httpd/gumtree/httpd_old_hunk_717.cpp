#endif



    /* Since we are reading from one buffer and writing to another,

     * it is unsafe to do a soft_timeout here, at least until the proxy

     * has its own timeout handler which can set both buffers to EOUT.

     */

    ap_hard_timeout("proxy send body", r);



    while (!con->aborted && f != NULL) {

	n = ap_bread(f, buf, IOBUFSIZE);

	if (n == -1) {		/* input error */

	    if (f2 != NULL)

		f2 = ap_proxy_cache_error(c);

	    break;

	}

	if (n == 0)

	    break;		/* EOF */

	o = 0;

	total_bytes_sent += n;



	if (f2 != NULL)

	    if (ap_bwrite(f2, buf, n) != n)

		f2 = ap_proxy_cache_error(c);



	while (n && !con->aborted) {

	    w = ap_bwrite(con->client, &buf[o], n);

	    if (w <= 0) {

		if (f2 != NULL) {

		    ap_pclosef(c->req->pool, c->fp->fd);

		    c->fp = NULL;

		    f2 = NULL;

		    con->aborted = 1;

		    unlink(c->tempfile);

		}

		break;

	    }

	    ap_reset_timeout(r);	/* reset timeout after successful write */

	    n -= w;

	    o += w;

	}

    }

    if (!con->aborted)

	ap_bflush(con->client);



    ap_kill_timeout(r);

    return total_bytes_sent;

}



/*

 * Read a header from the array, returning the first entry

 */

struct hdr_entry *

