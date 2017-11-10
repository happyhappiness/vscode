static int verify(struct passwd_ctx *ctx, const char *hash)
{
    apr_status_t rv;
    int ret;

    if (ctx->passwd == NULL && (ret = get_password(ctx)) != 0)
       return ret;
    rv = apr_password_validate(ctx->passwd, hash);
    if (rv == APR_SUCCESS)
        return 0;
    if (APR_STATUS_IS_EMISMATCH(rv)) {
        ctx->errstr = "password verification failed";
        return ERR_PWMISMATCH;
    }
    ctx->errstr = apr_psprintf(ctx->pool, "Could not verify password: %pm",
                               &rv);
    return ERR_GENERAL;
}