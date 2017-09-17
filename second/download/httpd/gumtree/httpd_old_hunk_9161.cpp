                case token_ge:
                case token_gt:
                case token_le:
                case token_lt:
                    break;
                default:
                    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                                "Invalid expression \"%s\" in file %s",
                                expr, r->filename);
                    ap_rputs(error, r);
                    goto RETURN;
                }
                break;
