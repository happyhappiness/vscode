            break;

        default:
            break;
        }

        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr, r->filename);
        *was_error = 1;
        return 0;
    }

    DEBUG_DUMP_TREE(ctx, root);
