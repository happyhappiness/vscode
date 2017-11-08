static size_t subst_str(link_ctx *ctx, int start, int end, const char *ns)
{
    int olen, nlen, plen;
    int delta;
    char *p;
    
    olen = end - start;
    nlen = (int)strlen(ns);
    delta = nlen - olen;
    plen = ctx->slen + delta + 1;
    p = apr_pcalloc(ctx->pool, plen);
    strncpy(p, ctx->s, start);
    strncpy(p + start, ns, nlen);
    strcpy(p + start + nlen, ctx->s + end);
    ctx->s = p;
    ctx->slen = (int)strlen(p);
    if (ctx->i >= end) {
        ctx->i += delta;
    }
    return nlen; 
}