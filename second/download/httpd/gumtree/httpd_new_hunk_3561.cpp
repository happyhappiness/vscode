        case 'f':
            if (format) {
                apr_file_printf(errfile, "Error: -f can only be passed once" NL NL);
                usage();
                return 1;
            }
            format = apr_pstrdup(pool, opt_arg);
            break;
        case 'i':
            if (input) {
                apr_file_printf(errfile, "Error: -i can only be passed once" NL NL);
                usage();
                return 1;
            }
            input = apr_pstrdup(pool, opt_arg);
            break;
        case 'o':
            if (output) {
                apr_file_printf(errfile, "Error: -o can only be passed once" NL NL);
                usage();
                return 1;
            }
            output = apr_pstrdup(pool, opt_arg);
            break;
        }
    }

    if (rv != APR_EOF) {
        apr_file_printf(errfile, "Error: Parsing Arguments Failed" NL NL);
