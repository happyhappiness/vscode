                node = NULL;
                break;
            }
        }

        if (node && node->frec) {
            return add_any_filter_handle(node->frec, ctx, r, c, r_filters,
                                         p_filters, c_filters);
        }
    }

    ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                 "an unknown filter was not added: %s", name);
