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
