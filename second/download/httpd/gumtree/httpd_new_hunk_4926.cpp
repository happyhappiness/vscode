            case 'e':
                csvperc = strdup(opt_arg);
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
