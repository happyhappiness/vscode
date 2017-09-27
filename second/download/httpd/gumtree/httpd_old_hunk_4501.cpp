            case 'f':
                if (strncasecmp(opt_arg, "ALL", 3) == 0) {
                    meth = SSLv23_client_method();
#ifndef OPENSSL_NO_SSL2
                } else if (strncasecmp(opt_arg, "SSL2", 4) == 0) {
                    meth = SSLv2_client_method();
#endif
#ifndef OPENSSL_NO_SSL3
                } else if (strncasecmp(opt_arg, "SSL3", 4) == 0) {
                    meth = SSLv3_client_method();
#endif
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
