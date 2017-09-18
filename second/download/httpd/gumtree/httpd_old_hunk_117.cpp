                    current->token.type = token_group;
                    break;
                }
                current = current->parent;
            }
            if (current == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                            "Unmatched ')' in \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            break;
