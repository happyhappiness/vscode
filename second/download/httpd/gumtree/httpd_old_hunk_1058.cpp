
static void read_connection(struct connection * c)
{
    apr_size_t r;
    apr_status_t status;
    char *part;
    char respcode[4];		/* 3 digits and null */

    r = sizeof(buffer);
#ifdef USE_SSL
    if (ssl == 1)
    {
        status = SSL_read (c->ssl, buffer, r);
        if (status <= 0) {
            good++; c->read = 0;
            if (status < 0) printf("SSL read failed - closing connection\n");
            close_connection(c);
            return;
        }
    r = status;
    }
    else {
#endif
    status = apr_recv(c->aprsock, buffer, &r);
    if (APR_STATUS_IS_EAGAIN(status))
	return;
    else if (r == 0 && APR_STATUS_IS_EOF(status)) {
	good++;
	close_connection(c);
	return;
    }
    /* catch legitimate fatal apr_recv errors */
    else if (status != APR_SUCCESS) {
        err_except++; /* XXX: is this the right error counter? */
        /* XXX: Should errors here be fatal, or should we allow a
         * certain number of them before completely failing? -aaron */
        apr_err("apr_recv", status);
    }
#ifdef USE_SSL
    }
#endif

    totalread += r;
    if (c->read == 0) {
	c->beginread = apr_time_now();
    }
    c->read += r;
