		status, inbytes_left, outbytes_left);
	exit(1);
    }
#endif				/* NOT_ASCII */

    /* This only needs to be done once */
    if ((rv = apr_sockaddr_info_get(&destsa, connecthost, APR_UNSPEC, connectport, 0, cntxt))
	!= APR_SUCCESS) {
	char buf[120];
	apr_snprintf(buf, sizeof(buf),
		     "apr_sockaddr_info_get() for %s", connecthost);
	apr_err(buf, rv);
