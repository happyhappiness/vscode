                    }
                } while(0);
                break;

            case 'p':
                if (proxypath) {
                    usage(apr_psprintf(pool, "The option '%c' cannot be specified more than once", (int)opt));
                }
                proxypath = apr_pstrdup(pool, arg);
                if ((status = apr_filepath_set(proxypath, pool)) != APR_SUCCESS) {
                    usage(apr_psprintf(pool, "Could not set filepath to '%s': %s",
                                       proxypath, apr_strerror(status, errmsg, sizeof errmsg)));
                }
                break;

            case 'P':
                if (pidfilename) {
                    usage(apr_psprintf(pool, "The option '%c' cannot be specified more than once", (int)opt));
                }
                pidfilename = apr_pstrdup(pool, arg);
                break;

            } /* switch */
        } /* else */
    } /* while */

    if (argc <= 1) {
        usage(NULL);
    }

    if (o->ind != argc) {
         usage("Additional parameters specified on the command line, aborting");
    }

    if (isdaemon && repeat <= 0) {
         usage("Option -d must be greater than zero");
    }

