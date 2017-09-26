    /* Save a copy for the proxy */
    fullurl = apr_pstrdup(cntxt, url);

    if (strlen(url) > 7 && strncmp(url, "http://", 7) == 0) {
	url += 7;
#ifdef USE_SSL
        is_ssl = 0;
#endif
    }
    else
#ifdef USE_SSL
    if (strlen(url) > 8 && strncmp(url, "https://", 8) == 0) {
	url += 8;
        is_ssl = 1;
    }
#else
    if (strlen(url) > 8 && strncmp(url, "https://", 8) == 0) {
	fprintf(stderr, "SSL not compiled in; no https support\n");
	exit(1);
    }
