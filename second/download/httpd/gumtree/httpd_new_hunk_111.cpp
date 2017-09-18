            case token_lbrace:
            case token_not:
                new->parent = current;
                current = current->right = new;
                break;
            default:
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            break;
