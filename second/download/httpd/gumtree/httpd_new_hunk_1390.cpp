                case token_le:

                case token_lt:

                    break;

                case token_string:

                case token_group:

                default:

                    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

                                "Invalid expression \"%s\" in file %s",

                                expr, r->filename);

                    ap_rputs(error, r);

                    goto RETURN;

                }

                break;

