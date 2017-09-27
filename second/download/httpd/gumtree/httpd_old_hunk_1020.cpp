#endif
    SSL_load_error_strings();
    SSL_library_init();
    bio_out=BIO_new_fp(stdout,BIO_NOCLOSE);
    bio_err=BIO_new_fp(stderr,BIO_NOCLOSE);

    /* TODO: Allow force SSLv2_client_method() (TLSv1?) */
    if (!(ctx = SSL_CTX_new(SSLv23_client_method()))) {
	fprintf(stderr, "Could not init SSL CTX");
	ERR_print_errors_fp(stderr);
	exit(1);
    }
    SSL_CTX_set_options(ctx, SSL_OP_ALL);
#ifdef USE_THREADS
    ssl_util_thread_setup(cntxt);
#endif
#endif
#ifdef SIGPIPE
    apr_signal(SIGPIPE, SIG_IGN);       /* Ignore writes to connections that
					 * have been closed at the other end. */
#endif
    copyright();
