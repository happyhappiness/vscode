static const char *dav_fs_getetag(const dav_resource *resource)
{
    dav_resource_private *ctx = resource->info;

    if (!resource->exists)
        return apr_pstrdup(ctx->pool, "");

    if (ctx->finfo.filetype != 0) {
        return apr_psprintf(ctx->pool, "\"%lx-%lx-%lx\"",
                           (unsigned long) ctx->finfo.inode,
                           (unsigned long) ctx->finfo.size,
                           (unsigned long) ctx->finfo.mtime);
    }

    return apr_psprintf(ctx->pool, "\"%lx\"", (unsigned long) ctx->finfo.mtime);
}