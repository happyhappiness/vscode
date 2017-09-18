    if (ctx->limit) {
        /* FIXME: Note that we might get slightly confused on chunked inputs
         * as we'd need to compensate for the chunk lengths which may not
         * really count.  This seems to be up for interpretation.  */
        ctx->limit_used += totalread;
        if (ctx->limit < ctx->limit_used) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, f->r,
                          "Read content-length of %" APR_OFF_T_FMT 
                          " is larger than the configured limit"
                          " of %" APR_OFF_T_FMT, ctx->limit_used, ctx->limit);
            ap_die(HTTP_REQUEST_ENTITY_TOO_LARGE, f->r);
            return APR_EGENERAL;
        }
    }

    return APR_SUCCESS;
}

