	    printf("Send request timed out!\n");
	    close_connection(c);
	    return;
	}

#ifdef USE_SSL
        if (ssl == 1) {
            apr_size_t e_ssl;
            e_ssl = SSL_write(c->ssl,request + c->rwrote, l);
            if (e_ssl != l)
            {
                printf("SSL write failed - closing connection\n");
                close_connection (c);
                return;
            }
            l = e_ssl;
        }
        else
#endif
	e = apr_send(c->aprsock, request + c->rwrote, &l);

	/*
	 * Bail early on the most common case
	 */
	if (l == c->rwrite)
	    break;

#ifdef USE_SSL
        if (ssl != 1)
#endif
	if (e != APR_SUCCESS) {
	    /*
	     * Let's hope this traps EWOULDBLOCK too !
	     */
	    if (!APR_STATUS_IS_EAGAIN(e)) {
		epipe++;
