            case TOKEN_ACCESS:
            case TOKEN_LBRACE:
                root = current = new;
                continue;

            default:
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr,
                              r->filename);
                *was_error = 1;
                return 0;
            }
        }
