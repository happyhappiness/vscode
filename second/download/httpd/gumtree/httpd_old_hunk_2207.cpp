                    current->token.type = token_group;

                    break;

                }

                current = current->parent;

            }

            if (current == (struct parse_node *) NULL) {

                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                            "Unmatched ')' in \"%s\" in file %s",

			    expr, r->filename);

                ap_rputs(error, r);

                goto RETURN;

            }

            break;

