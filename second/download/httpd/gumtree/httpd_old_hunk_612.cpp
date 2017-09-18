				 * connections. */
    }
    else
	heartbeatres = 0;

#ifdef USE_SSL
    SSL_library_init();
    if (!(ctx = SSL_CTX_new(SSLv2_client_method()))) {
	fprintf(stderr, "Could not init SSL CTX");
	ERR_print_errors_fp(stderr);
	exit(1);
    }
#endif
#if SIGPIPE
    signal(SIGPIPE, SIG_IGN);	        /* Ignore writes to connections that
					 * have been closed at the other end. */
#endif
    copyright();
    test();
    apr_pool_destroy(cntxt);

