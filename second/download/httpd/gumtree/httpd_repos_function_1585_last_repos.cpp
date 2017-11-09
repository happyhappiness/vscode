static APR_INLINE const char *la_u(rewrite_ctx *ctx)
{
    rewrite_perdir_conf *conf;

    if (*ctx->uri == '/') {
        return ctx->uri;
    }

    conf = ap_get_module_config(ctx->r->per_dir_config, &rewrite_module);

    return apr_pstrcat(ctx->r->pool, conf->baseurl
                                     ? conf->baseurl : conf->directory,
                       ctx->uri, NULL);
}