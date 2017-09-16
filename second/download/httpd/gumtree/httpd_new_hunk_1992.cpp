            case token_le:

            case token_lt:

                new->parent = current;

                current = current->right = new;

                break;

            default:

                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

                            "Invalid expression \"%s\" in file %s",

                            expr, r->filename);

                ap_rputs(error, r);

                goto RETURN;

            }

            break;

