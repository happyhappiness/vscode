{
    unsigned int data_len;

    /* Retrieve any corresponding session from the distributed cache context */
    if (!DC_CTX_get_session(ctx->dc, id, idlen, dest, *destlen, &data_len)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "distributed scache 'retrieve' MISS");
        return APR_EGENERAL;
    }
    if (data_len > *destlen) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'retrieve' OVERFLOW");
        return APR_ENOSPC;
    }
    *destlen = data_len;
