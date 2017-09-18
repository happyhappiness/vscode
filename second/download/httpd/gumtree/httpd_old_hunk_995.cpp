	{
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                     "Error: %d with ioctlsocket(flag SO_TLS_ENABLE)", WSAGetLastError());
		return rcode;
	}

    /* setup the socket for SSL */
    memset (&sWS2Opts, 0, sizeof(sWS2Opts));
    memset (&sNWTLSOpts, 0, sizeof(sNWTLSOpts));
    sWS2Opts.options = &sNWTLSOpts;

    if (numcerts) {
