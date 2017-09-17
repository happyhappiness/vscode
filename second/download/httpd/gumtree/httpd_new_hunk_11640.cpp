#endif
            current->done = 1;
            current = current->parent;
            break;

        case token_lbrace:
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                        "Unmatched '(' in \"%s\" in file %s",
                        expr, r->filename);
            ap_rputs(error, r);
            goto RETURN;

        case token_rbrace:
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                        "Unmatched ')' in \"%s\" in file %s",
                        expr, r->filename);
            ap_rputs(error, r);
            goto RETURN;

        default:
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			"bad token type");
            ap_rputs(error, r);
            goto RETURN;
        }
    }

