    apr_size_t r;
    apr_status_t status;
    char *part;
    char respcode[4];		/* 3 digits and null */

    r = sizeof(buffer);
    status = apr_recv(c->aprsock, buffer, &r);
    if (APR_STATUS_IS_EAGAIN(status))
	return;
    else if (r == 0 && APR_STATUS_IS_EOF(status)) {
	good++;
	close_connection(c);
