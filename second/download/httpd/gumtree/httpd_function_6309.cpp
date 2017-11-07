static int add_header(ngh_ctx *ctx, const char *key, const char *value)
{
    nghttp2_nv *nv = &(ctx->ngh)->nv[(ctx->ngh)->nvlen++];
    const char *p;

    if (!ctx->unsafe) {
        if ((p = inv_field_name_chr(key))) {
            ap_log_perror(APLOG_MARK, APLOG_TRACE1, APR_EINVAL, ctx->p,
                          "h2_request: head field '%s: %s' has invalid char %s", 
                          key, value, p);
            ctx->status = APR_EINVAL;
            return 0;
        }
        if ((p = inv_field_value_chr(value))) {
            ap_log_perror(APLOG_MARK, APLOG_TRACE1, APR_EINVAL, ctx->p,
                          "h2_request: head field '%s: %s' has invalid char %s", 
                          key, value, p);
            ctx->status = APR_EINVAL;
            return 0;
        }
    }
    nv->name = (uint8_t*)key;
    nv->namelen = strlen(key);
    nv->value = (uint8_t*)value;
    nv->valuelen = strlen(value);
    
    return 1;
}