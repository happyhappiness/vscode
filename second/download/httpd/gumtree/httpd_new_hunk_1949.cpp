                    }
                } while(0);
                break;

            case 'p':
                if (proxypath) {
                    usage_repeated_arg(pool, opt);
                }
                proxypath = apr_pstrdup(pool, arg);
                if ((status = apr_filepath_set(proxypath, pool)) != APR_SUCCESS) {
                    usage(apr_psprintf(pool, "Could not set filepath to '%s': %s",
                                       proxypath, apr_strerror(status, errmsg, sizeof errmsg)));
                }
                break;

            case 'P':
                if (pidfilename) {
                    usage_repeated_arg(pool, opt);
                }
                pidfilename = apr_pstrdup(pool, arg);
                break;

            } /* switch */
        } /* else */
    } /* while */

    if (argc <= 1) {
        usage(NULL);
    }

    if (o->ind < argc) {
        int deleted = 0;
        int error = 0;
        if (isdaemon) {
            usage("Option -d cannot be used with URL arguments, aborting");
        }
        if (intelligent) {
            usage("Option -i cannot be used with URL arguments, aborting");
        }
        if (limit_found) {
            usage("Option -l cannot be used with URL arguments, aborting");
        }
        while (o->ind < argc) {
            status = delete_url(pool, proxypath, argv[o->ind]);
            if (APR_SUCCESS == status) {
                if (verbose) {
                    apr_file_printf(errfile, "Removed: %s" APR_EOL_STR,
                            argv[o->ind]);
                }
                deleted = 1;
            }
            else if (APR_ENOENT == status) {
                if (verbose) {
                    apr_file_printf(errfile, "Not cached: %s" APR_EOL_STR,
                            argv[o->ind]);
                }
            }
            else {
                if (verbose) {
                    apr_file_printf(errfile, "Error while removed: %s" APR_EOL_STR,
                            argv[o->ind]);
                }
                error = 1;
            }
            o->ind++;
        }
        return error ? 1 : deleted ? 0 : 2;
    }

    if (isdaemon && repeat <= 0) {
         usage("Option -d must be greater than zero");
    }

