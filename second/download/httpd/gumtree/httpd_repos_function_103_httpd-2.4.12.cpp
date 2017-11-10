int main(int argc, const char * const argv[])
{
    int l;
    char tmp[1024];
    apr_status_t status;
    apr_getopt_t *opt;
    const char *opt_arg;
    char c;
#ifdef USE_SSL
    AB_SSL_METHOD_CONST SSL_METHOD *meth = SSLv23_client_method();
#endif

    /* table defaults  */
    tablestring = "";
    trstring = "";
    tdstring = "bgcolor=white";
    cookie = "";
    auth = "";
    proxyhost = "";
    hdrs = "";

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);
    apr_pool_create(&cntxt, NULL);
    apr_pool_abort_set(abort_on_oom, cntxt);

#ifdef NOT_ASCII
    status = apr_xlate_open(&to_ascii, "ISO-8859-1", APR_DEFAULT_CHARSET, cntxt);
    if (status) {
        fprintf(stderr, "apr_xlate_open(to ASCII)->%d\n", status);
        exit(1);
    }
    status = apr_xlate_open(&from_ascii, APR_DEFAULT_CHARSET, "ISO-8859-1", cntxt);
    if (status) {
        fprintf(stderr, "apr_xlate_open(from ASCII)->%d\n", status);
        exit(1);
    }
    status = apr_base64init_ebcdic(to_ascii, from_ascii);
    if (status) {
        fprintf(stderr, "apr_base64init_ebcdic()->%d\n", status);
        exit(1);
    }
#endif

    myhost = NULL; /* 0.0.0.0 or :: */

    apr_getopt_init(&opt, cntxt, argc, argv);
    while ((status = apr_getopt(opt, "n:c:t:s:b:T:p:u:v:lrkVhwix:y:z:C:H:P:A:g:X:de:SqB:m:"
#ifdef USE_SSL
            "Z:f:"
#endif
            ,&c, &opt_arg)) == APR_SUCCESS) {
        switch (c) {
            case 'n':
                requests = atoi(opt_arg);
                if (requests <= 0) {
                    err("Invalid number of requests\n");
                }
                break;
            case 'k':
                keepalive = 1;
                break;
            case 'q':
                heartbeatres = 0;
                break;
            case 'c':
                concurrency = atoi(opt_arg);
                break;
            case 'b':
                windowsize = atoi(opt_arg);
                break;
            case 'i':
                if (method != NO_METH)
                    err("Cannot mix HEAD with other methods\n");
                method = HEAD;
                break;
            case 'g':
                gnuplot = xstrdup(opt_arg);
                break;
            case 'd':
                percentile = 0;
                break;
            case 'e':
                csvperc = xstrdup(opt_arg);
                break;
            case 'S':
                confidence = 0;
                break;
            case 's':
                aprtimeout = apr_time_from_sec(atoi(opt_arg)); /* timeout value */
                break;
            case 'p':
                if (method != NO_METH)
                    err("Cannot mix POST with other methods\n");
                if (open_postfile(opt_arg) != APR_SUCCESS) {
                    exit(1);
                }
                method = POST;
                send_body = 1;
                break;
            case 'u':
                if (method != NO_METH)
                    err("Cannot mix PUT with other methods\n");
                if (open_postfile(opt_arg) != APR_SUCCESS) {
                    exit(1);
                }
                method = PUT;
                send_body = 1;
                break;
            case 'l':
                nolength = 1;
                break;
            case 'r':
                recverrok = 1;
                break;
            case 'v':
                verbosity = atoi(opt_arg);
                break;
            case 't':
                tlimit = atoi(opt_arg);
                requests = MAX_REQUESTS;    /* need to size data array on
                                             * something */
                break;
            case 'T':
                content_type = apr_pstrdup(cntxt, opt_arg);
                break;
            case 'C':
                cookie = apr_pstrcat(cntxt, "Cookie: ", opt_arg, "\r\n", NULL);
                break;
            case 'A':
                /*
                 * assume username passwd already to be in colon separated form.
                 * Ready to be uu-encoded.
                 */
                while (apr_isspace(*opt_arg))
                    opt_arg++;
                if (apr_base64_encode_len(strlen(opt_arg)) > sizeof(tmp)) {
                    err("Authentication credentials too long\n");
                }
                l = apr_base64_encode(tmp, opt_arg, strlen(opt_arg));
                tmp[l] = '\0';

                auth = apr_pstrcat(cntxt, auth, "Authorization: Basic ", tmp,
                                       "\r\n", NULL);
                break;
            case 'P':
                /*
                 * assume username passwd already to be in colon separated form.
                 */
                while (apr_isspace(*opt_arg))
                opt_arg++;
                if (apr_base64_encode_len(strlen(opt_arg)) > sizeof(tmp)) {
                    err("Proxy credentials too long\n");
                }
                l = apr_base64_encode(tmp, opt_arg, strlen(opt_arg));
                tmp[l] = '\0';

                auth = apr_pstrcat(cntxt, auth, "Proxy-Authorization: Basic ",
                                       tmp, "\r\n", NULL);
                break;
            case 'H':
                hdrs = apr_pstrcat(cntxt, hdrs, opt_arg, "\r\n", NULL);
                /*
                 * allow override of some of the common headers that ab adds
                 */
                if (strncasecmp(opt_arg, "Host:", 5) == 0) {
                    opt_host = 1;
                } else if (strncasecmp(opt_arg, "Accept:", 7) == 0) {
                    opt_accept = 1;
                } else if (strncasecmp(opt_arg, "User-Agent:", 11) == 0) {
                    opt_useragent = 1;
                }
                break;
            case 'w':
                use_html = 1;
                break;
                /*
                 * if any of the following three are used, turn on html output
                 * automatically
                 */
            case 'x':
                use_html = 1;
                tablestring = opt_arg;
                break;
            case 'X':
                {
                    char *p;
                    /*
                     * assume proxy-name[:port]
                     */
                    if ((p = strchr(opt_arg, ':'))) {
                        *p = '\0';
                        p++;
                        proxyport = atoi(p);
                    }
                    proxyhost = apr_pstrdup(cntxt, opt_arg);
                    isproxy = 1;
                }
                break;
            case 'y':
                use_html = 1;
                trstring = opt_arg;
                break;
            case 'z':
                use_html = 1;
                tdstring = opt_arg;
                break;
            case 'h':
                usage(argv[0]);
                break;
            case 'V':
                copyright();
                return 0;
            case 'B':
                myhost = apr_pstrdup(cntxt, opt_arg);
                break;
#ifdef USE_SSL
            case 'Z':
                ssl_cipher = strdup(opt_arg);
                break;
            case 'm':
                method = CUSTOM_METHOD;
                method_str[CUSTOM_METHOD] = strdup(opt_arg);
                break;
            case 'f':
                if (strncasecmp(opt_arg, "ALL", 3) == 0) {
                    meth = SSLv23_client_method();
#ifndef OPENSSL_NO_SSL2
                } else if (strncasecmp(opt_arg, "SSL2", 4) == 0) {
                    meth = SSLv2_client_method();
#endif
                } else if (strncasecmp(opt_arg, "SSL3", 4) == 0) {
                    meth = SSLv3_client_method();
#ifdef HAVE_TLSV1_X
                } else if (strncasecmp(opt_arg, "TLS1.1", 6) == 0) {
                    meth = TLSv1_1_client_method();
                } else if (strncasecmp(opt_arg, "TLS1.2", 6) == 0) {
                    meth = TLSv1_2_client_method();
#endif
                } else if (strncasecmp(opt_arg, "TLS1", 4) == 0) {
                    meth = TLSv1_client_method();
                }
                break;
#endif
        }
    }

    if (opt->ind != argc - 1) {
        fprintf(stderr, "%s: wrong number of arguments\n", argv[0]);
        usage(argv[0]);
    }

    if (method == NO_METH) {
        method = GET;
    }

    if (parse_url(apr_pstrdup(cntxt, opt->argv[opt->ind++]))) {
        fprintf(stderr, "%s: invalid URL\n", argv[0]);
        usage(argv[0]);
    }

    if ((concurrency < 0) || (concurrency > MAX_CONCURRENCY)) {
        fprintf(stderr, "%s: Invalid Concurrency [Range 0..%d]\n",
                argv[0], MAX_CONCURRENCY);
        usage(argv[0]);
    }

    if (concurrency > requests) {
        fprintf(stderr, "%s: Cannot use concurrency level greater than "
                "total number of requests\n", argv[0]);
        usage(argv[0]);
    }

    if ((heartbeatres) && (requests > 150)) {
        heartbeatres = requests / 10;   /* Print line every 10% of requests */
        if (heartbeatres < 100)
            heartbeatres = 100; /* but never more often than once every 100
                                 * connections. */
    }
    else
        heartbeatres = 0;

#ifdef USE_SSL
#ifdef RSAREF
    R_malloc_init();
#else
    CRYPTO_malloc_init();
#endif
    SSL_load_error_strings();
    SSL_library_init();
    bio_out=BIO_new_fp(stdout,BIO_NOCLOSE);
    bio_err=BIO_new_fp(stderr,BIO_NOCLOSE);

    if (!(ssl_ctx = SSL_CTX_new(meth))) {
        BIO_printf(bio_err, "Could not initialize SSL Context.\n");
        ERR_print_errors(bio_err);
        exit(1);
    }
    SSL_CTX_set_options(ssl_ctx, SSL_OP_ALL);
#ifdef SSL_MODE_RELEASE_BUFFERS
    /* Keep memory usage as low as possible */
    SSL_CTX_set_mode (ssl_ctx, SSL_MODE_RELEASE_BUFFERS);
#endif
    if (ssl_cipher != NULL) {
        if (!SSL_CTX_set_cipher_list(ssl_ctx, ssl_cipher)) {
            fprintf(stderr, "error setting cipher list [%s]\n", ssl_cipher);
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    }
    if (verbosity >= 3) {
        SSL_CTX_set_info_callback(ssl_ctx, ssl_state_cb);
    }
#endif
#ifdef SIGPIPE
    apr_signal(SIGPIPE, SIG_IGN);       /* Ignore writes to connections that
                                         * have been closed at the other end. */
#endif
    copyright();
    test();
    apr_pool_destroy(cntxt);

    return 0;
}