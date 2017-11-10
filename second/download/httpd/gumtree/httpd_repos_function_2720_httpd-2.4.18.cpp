static void fix_skipto(request_rec* r, xml2ctx* ctx)
{
    apr_status_t rv;
    xml2cfg* cfg = ap_get_module_config(r->per_dir_config, &xml2enc_module);
    if ((cfg->skipto != NULL) && (ctx->flags & ENC_SKIPTO)) {
        int found = 0;
        char* p = ap_strchr(ctx->buf, '<');
        tattr* starts = (tattr*) cfg->skipto->elts;
        while (!found && p && *p) {
            int i;
            for (i = 0; i < cfg->skipto->nelts; ++i) {
                if (!strncasecmp(p+1, starts[i].val, strlen(starts[i].val))) {
                    /* found a starting element. Strip all that comes before. */
                    apr_bucket* b;
                    apr_bucket* bstart;
                    rv = apr_brigade_partition(ctx->bbsave, (p-ctx->buf),
                                               &bstart);
                    ap_assert(rv == APR_SUCCESS);
                    while (b = APR_BRIGADE_FIRST(ctx->bbsave), b != bstart) {
                        apr_bucket_delete(b);
                    }
                    ctx->bytes -= (p-ctx->buf);
                    ctx->buf = p ;
                    found = 1;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01428)
                                  "Skipped to first <%s> element",
                                  starts[i].val) ;
                    break;
                }
            }
            p = ap_strchr(p+1, '<');
        }
        if (p == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01429)
                          "Failed to find start of recognised HTML!");
        }
    }
}