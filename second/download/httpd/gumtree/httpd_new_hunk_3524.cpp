        if (node && node->frec) {
            return add_any_filter_handle(node->frec, ctx, r, c, r_filters,
                                         p_filters, c_filters);
        }
    }

    ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, r ? r->connection : c, APLOGNO(00082)
                  "an unknown filter was not added: %s", name);
    return NULL;
}

AP_DECLARE(ap_filter_t *) ap_add_input_filter(const char *name, void *ctx,
                                              request_rec *r, conn_rec *c)
{
