        case token_le:

        case token_lt:

#ifdef DEBUG_INCLUDE

            ap_rputs("     Token: eq/ne/ge/gt/le/lt\n", r);

#endif

            if (current == (struct parse_node *) NULL) {

                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

                            "Invalid expression \"%s\" in file %s",

                            expr, r->filename);

                ap_rputs(error, r);

                goto RETURN;

            }

            /* Percolate upwards */

