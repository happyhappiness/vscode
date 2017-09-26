                        else if (*end &&        /* neither empty nor [Bb] */
                                 ((*end != 'B' && *end != 'b') || end[1])) {
                            rv = APR_EGENERAL;
                        }
                    }
                    if (rv != APR_SUCCESS) {
                        apr_file_printf(errfile, "Invalid limit: %s"
                                                 APR_EOL_STR APR_EOL_STR, arg);
                        usage();
                    }
                } while(0);
                break;

            case 'p':
                if (proxypath) {
                    usage();
                }
                proxypath = apr_pstrdup(pool, arg);
                if (apr_filepath_set(proxypath, pool) != APR_SUCCESS) {
                    usage();
                }
                break;
            } /* switch */
        } /* else */
    } /* while */

    if (o->ind != argc) {
         usage();
    }

    if (isdaemon && (repeat <= 0 || verbose || realclean || dryrun)) {
         usage();
    }

    if (!isdaemon && intelligent) {
         usage();
    }

    if (!proxypath || max <= 0) {
         usage();
    }

    if (apr_filepath_get(&path, 0, pool) != APR_SUCCESS) {
        usage();
    }
    baselen = strlen(path);

#ifndef DEBUG
    if (isdaemon) {
        apr_file_close(errfile);
