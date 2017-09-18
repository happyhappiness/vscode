            current->value = (current->token.value[0] != '\0');
            current->done = 1;
            current = current->parent;
            break;

        case token_re:
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "No operator before regex of expr \"%s\" in file %s",
                          expr, r->filename);
            *was_error = 1;
            return retval;

        case token_and:
