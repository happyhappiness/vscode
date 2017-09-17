        case token_and:
        case token_or:
#ifdef DEBUG_INCLUDE
            ap_rputs("     Token: and/or\n", r);
#endif
            if (current == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                ap_rputs(error, r);
                goto RETURN;
            }
            /* Percolate upwards */
