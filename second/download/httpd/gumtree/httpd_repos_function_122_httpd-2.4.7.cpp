static int mkrecord(struct passwd_ctx *ctx, char *user)
{
    char hash_str[MAX_STRING_LEN];
    int ret;
    ctx->out = hash_str;
    ctx->out_len = sizeof(hash_str);

    ret = mkhash(ctx);
    if (ret)
        return ret;

    ctx->out = apr_pstrcat(ctx->pool, user, ":", hash_str, NL, NULL);
    if (strlen(ctx->out) >= MAX_STRING_LEN) {
        ctx->errstr = "resultant record too long";
        return ERR_OVERFLOW;
    }
    return 0;
}