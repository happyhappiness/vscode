static const char *direct_chunkreader(lua_State *lvm, void *udata,
                                      size_t *plen)
{
    const char *p;
    struct cr_ctx *ctx = udata;

    if (ctx->startline) {
        *plen = ctx->startline > N_LF ? N_LF : ctx->startline;
        ctx->startline -= *plen;
        return lf;
    }
    *plen = config_getstr(ctx->cfp, ctx->buf, HUGE_STRING_LEN);

    for (p = ctx->buf; isspace(*p); ++p);
    if (p[0] == '<' && p[1] == '/') {
        apr_size_t i = 0;
        while (i < strlen(ctx->endstr)) {
            if (tolower(p[i + 2]) != ctx->endstr[i])
                return ctx->buf;
            ++i;
        }
        *plen = 0;
        return NULL;
    }
    /*fprintf(stderr, "buf read: %s\n", ctx->buf); */
    return ctx->buf;
}