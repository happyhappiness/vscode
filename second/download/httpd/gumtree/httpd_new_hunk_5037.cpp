 * Make a password record from the given information.  A zero return
 * indicates success; on failure, ctx->errstr points to the error message.
 */
int mkhash(struct passwd_ctx *ctx)
{
    char *pw;
    char salt[16];
    apr_status_t rv;
    int ret = 0;
#if CRYPT_ALGO_SUPPORTED
    char *cbuf;
#endif

    if (ctx->cost != 0 && ctx->alg != ALG_BCRYPT) {
        apr_file_printf(errfile,
                        "Warning: Ignoring -C argument for this algorithm." NL);
    }

    if (ctx->passwd == NULL) {
        if ((ret = get_password(ctx)) != 0)
            return ret;
    }
    pw = ctx->passwd;

    switch (ctx->alg) {
    case ALG_APSHA:
        /* XXX out >= 28 + strlen(sha1) chars - fixed len SHA */
        apr_sha1_base64(pw, strlen(pw), ctx->out);
        break;
