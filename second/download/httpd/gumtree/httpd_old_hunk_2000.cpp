        case token_or:

#ifdef DEBUG_INCLUDE

            ap_rputs("     Evaluate and/or\n", r);

#endif

            if (current->left == (struct parse_node *) NULL ||

                current->right == (struct parse_node *) NULL) {

                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                            "Invalid expression \"%s\" in file %s",

                            expr, r->filename);

                ap_rputs(error, r);

                goto RETURN;

            }

            if (!current->left->done) {

