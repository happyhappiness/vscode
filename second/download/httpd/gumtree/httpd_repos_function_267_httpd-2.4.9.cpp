static const char *dav_fs_getetag(const dav_resource *resource)
{
    dav_resource_private *ctx = resource->info;
    /* XXX: This should really honor the FileETag setting */

    if (!resource->exists)
        return apr_pstrdup(ctx->pool, "");

    if (ctx->finfo.filetype != APR_NOFILE) {
        return apr_psprintf(ctx->pool, "\"%" APR_UINT64_T_HEX_FMT "-%"
                            APR_UINT64_T_HEX_FMT "\"",
                            (apr_uint64_t) ctx->finfo.size,
                            (apr_uint64_t) ctx->finfo.mtime);
    }

    return apr_psprintf(ctx->pool, "\"%" APR_UINT64_T_HEX_FMT "\"",
                       (apr_uint64_t) ctx->finfo.mtime);
}