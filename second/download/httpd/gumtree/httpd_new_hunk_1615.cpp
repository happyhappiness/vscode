            ap_rputs("     Evaluate ge/gt/le/lt\n", r);
#endif
            if ((current->left == (struct parse_node *) NULL) ||
                (current->right == (struct parse_node *) NULL) ||
                (current->left->token.type != token_string) ||
                (current->right->token.type != token_string)) {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                ap_rputs(error, r);
                goto RETURN;
            }
            parse_string(r, current->left->token.value,
