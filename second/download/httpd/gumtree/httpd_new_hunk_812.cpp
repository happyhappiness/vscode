    apr_status_t status;
#ifdef NOT_ASCII
    apr_size_t inbytes_left, outbytes_left;
#endif

    if (isproxy) {
	connecthost = apr_pstrdup(cntxt, proxyhost);
	connectport = proxyport;
    }
    else {
	connecthost = apr_pstrdup(cntxt, hostname);
	connectport = port;
    }

    if (!use_html) {
	printf("Benchmarking %s ", hostname);
	if (isproxy)
