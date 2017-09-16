    } else {

        ap_hard_timeout("proxy send body", r);

        alt_to = 0;

    }

#endif



    while (ok) {

        if (alt_to)

            ap_hard_timeout("proxy send body", r);



	/* Read block from server */

	n = ap_bread(f, buf, IOBUFSIZE);



        if (alt_to)

            ap_kill_timeout(r);

        else

            ap_reset_timeout(r);



	if (n == -1) {		/* input error */

	    if (c != NULL)

		c = ap_proxy_cache_error(c);

	    break;

	}

	if (n == 0)

	    break;		/* EOF */

	o = 0;

	total_bytes_rcv += n;



	/* Write to cache first. */

        if (c != NULL && c->fp != NULL) {

            if (ap_bwrite(c->fp, &buf[0], n) != n) {

                c = ap_proxy_cache_error(c);

            } else {

                c->written += n;

            }

        }



	/* Write the block to the client, detect aborted transfers */

        while (n && !con->aborted) {

            if (alt_to)

                ap_soft_timeout("proxy send body", r);



            w = ap_bwrite(con->client, &buf[o], n);



            if (alt_to)

                ap_kill_timeout(r);

            else

                ap_reset_timeout(r);



            if (w <= 0) {

                if (c != NULL) {

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

                        unlink(c->tempfile);

			c = NULL;

                    }

                }

                con->aborted = 1;

                break;

            }

            n -= w;

