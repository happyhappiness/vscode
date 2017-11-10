static void dump_content(saxctxt *ctx)
{
    urlmap *m;
    char *found;
    size_t s_from, s_to;
    size_t match;
    char c = 0;
    int nmatch;
    ap_regmatch_t pmatch[10];
    char *subs;
    size_t len, offs;
    urlmap *themap = ctx->map;
#ifndef GO_FASTER
    int verbose = APLOGrtrace1(ctx->f->r);
#endif

    pappend(ctx, &c, 1);        /* append null byte */
        /* parse the text for URLs */
    for (m = themap; m; m = m->next) {
        if (!(m->flags & M_CDATA))
            continue;
        if (m->flags & M_REGEX) {
            nmatch = 10;
            offs = 0;
            while (!ap_regexec(m->from.r, ctx->buf+offs, nmatch, pmatch, 0)) {
                match = pmatch[0].rm_so;
                s_from = pmatch[0].rm_eo - match;
                subs = ap_pregsub(ctx->f->r->pool, m->to, ctx->buf+offs,
                                  nmatch, pmatch);
                s_to = strlen(subs);
                len = strlen(ctx->buf);
                offs += match;
                VERBOSEB(
                    const char *f = apr_pstrndup(ctx->f->r->pool,
                    ctx->buf + offs, s_from);
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, ctx->f->r,
                                  "C/RX: match at %s, substituting %s", f, subs);
                )
                if (s_to > s_from) {
                    preserve(ctx, s_to - s_from);
                    memmove(ctx->buf+offs+s_to, ctx->buf+offs+s_from,
                            len + 1 - s_from - offs);
                    memcpy(ctx->buf+offs, subs, s_to);
                }
                else {
                    memcpy(ctx->buf + offs, subs, s_to);
                    memmove(ctx->buf+offs+s_to, ctx->buf+offs+s_from,
                            len + 1 - s_from - offs);
                }
                offs += s_to;
            }
        }
        else {
            s_from = strlen(m->from.c);
            s_to = strlen(m->to);
            for (found = strstr(ctx->buf, m->from.c); found;
                 found = strstr(ctx->buf+match+s_to, m->from.c)) {
                match = found - ctx->buf;
                if ((m->flags & M_ATSTART) && (match != 0))
                    break;
                len = strlen(ctx->buf);
                if ((m->flags & M_ATEND) && (match < (len - s_from)))
                    continue;
                VERBOSE(ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, ctx->f->r,
                                      "C: matched %s, substituting %s",
                                      m->from.c, m->to));
                if (s_to > s_from) {
                    preserve(ctx, s_to - s_from);
                    memmove(ctx->buf+match+s_to, ctx->buf+match+s_from,
                            len + 1 - s_from - match);
                    memcpy(ctx->buf+match, m->to, s_to);
                }
                else {
                    memcpy(ctx->buf+match, m->to, s_to);
                    memmove(ctx->buf+match+s_to, ctx->buf+match+s_from,
                            len + 1 - s_from - match);
                }
            }
        }
    }
    AP_fwrite(ctx, ctx->buf, strlen(ctx->buf), 1);
}