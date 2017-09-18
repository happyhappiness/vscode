                case token_lt:
                    current = current->parent;
                    continue;
                case token_lbrace:
                    break;
                default:
                    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                                "Invalid expression \"%s\" in file %s",
                                expr, r->filename);
                    ap_rputs(error, r);
                    goto RETURN;
                }
                break;
