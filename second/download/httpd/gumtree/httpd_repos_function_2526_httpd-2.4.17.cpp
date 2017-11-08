static void pstartElement(void *ctxt, const xmlChar *uname,
                          const xmlChar** uattrs)
{
    int required_attrs;
    int num_match;
    size_t offs, len;
    char *subs;
    rewrite_t is_uri;
    const char** a;
    urlmap *m;
    size_t s_to, s_from, match;
    char *found;
    saxctxt *ctx = (saxctxt*) ctxt;
    size_t nmatch;
    ap_regmatch_t pmatch[10];
#ifndef GO_FASTER
    int verbose = APLOGrtrace1(ctx->f->r);
#endif
    apr_array_header_t *linkattrs;
    int i;
    const char *name = (const char*) uname;
    const char** attrs = (const char**) uattrs;
    const htmlElemDesc* desc = htmlTagLookup(uname);
    urlmap *themap = ctx->map;
#ifdef HAVE_STACK
    const void** descp;
#endif
    int enforce = 0;
    if ((ctx->cfg->doctype == fpi_html) || (ctx->cfg->doctype == fpi_xhtml)) {
        /* enforce html */
        enforce = 2;
        if (!desc || desc->depr)
            return;
    
    }
    else if ((ctx->cfg->doctype == fpi_html)
             || (ctx->cfg->doctype == fpi_xhtml)) {
        enforce = 1;
        /* enforce html legacy */
        if (!desc) {
            return;
        }
    }
    if (!desc && enforce) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->f->r, APLOGNO(01416)
                      "Bogus HTML element %s dropped", name);
        return;
    }
    if (desc && desc->depr && (enforce == 2)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->f->r, APLOGNO(01417)
                      "Deprecated HTML element %s dropped", name);
        return;
    }
#ifdef HAVE_STACK
    descp = apr_array_push(ctx->stack);
    *descp = desc;
    /* TODO - implement HTML "allowed here" */
#endif

    ap_fputc(ctx->f->next, ctx->bb, '<');
    ap_fputs(ctx->f->next, ctx->bb, name);

    required_attrs = 0;
    if ((enforce > 0) && (desc != NULL) && (desc->attrs_req != NULL))
        for (a = desc->attrs_req; *a; a++)
            ++required_attrs;

    if (attrs) {
        linkattrs = apr_hash_get(ctx->cfg->links, name, APR_HASH_KEY_STRING);
        for (a = attrs; *a; a += 2) {
            if (desc && enforce > 0) {
                switch (htmlAttrAllowed(desc, (xmlChar*)*a, 2-enforce)) {
                case HTML_INVALID:
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->f->r, APLOGNO(01418)
                                  "Bogus HTML attribute %s of %s dropped",
                                  *a, name);
                    continue;
                case HTML_DEPRECATED:
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->f->r, APLOGNO(01419)
                                  "Deprecated HTML attribute %s of %s dropped",
                                  *a, name);
                    continue;
                case HTML_REQUIRED:
                    required_attrs--;   /* cross off the number still needed */
                /* fallthrough - required implies valid */
                default:
                    break;
                }
            }
            ctx->offset = 0;
            if (a[1]) {
                pappend(ctx, a[1], strlen(a[1])+1);
                is_uri = ATTR_IGNORE;
                if (linkattrs) {
                    tattr *attrs = (tattr*) linkattrs->elts;
                    for (i=0; i < linkattrs->nelts; ++i) {
                        if (!strcmp(*a, attrs[i].val)) {
                            is_uri = ATTR_URI;
                            break;
                        }
                    }
                }
                if ((is_uri == ATTR_IGNORE) && ctx->cfg->extfix
                    && (ctx->cfg->events != NULL)) {
                    for (i=0; i < ctx->cfg->events->nelts; ++i) {
                        tattr *attrs = (tattr*) ctx->cfg->events->elts;
                        if (!strcmp(*a, attrs[i].val)) {
                            is_uri = ATTR_EVENT;
                            break;
                        }
                    }
                }
                switch (is_uri) {
                case ATTR_URI:
                    num_match = 0;
                    for (m = themap; m; m = m->next) {
                        if (!(m->flags & M_HTML))
                            continue;
                        if (m->flags & M_REGEX) {
                            nmatch = 10;
                            if (!ap_regexec(m->from.r, ctx->buf, nmatch,
                                            pmatch, 0)) {
                                ++num_match;
                                offs = match = pmatch[0].rm_so;
                                s_from = pmatch[0].rm_eo - match;
                                subs = ap_pregsub(ctx->f->r->pool, m->to,
                                                  ctx->buf, nmatch, pmatch);
                                VERBOSE({
                                    const char *f;
                                    f = apr_pstrndup(ctx->f->r->pool,
                                                     ctx->buf + offs, s_from);
                                    ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0,
                                                  ctx->f->r,
                                         "H/RX: match at %s, substituting %s",
                                                  f, subs);
                                })
                                s_to = strlen(subs);
                                len = strlen(ctx->buf);
                                if (s_to > s_from) {
                                    preserve(ctx, s_to - s_from);
                                    memmove(ctx->buf+offs+s_to,
                                            ctx->buf+offs+s_from,
                                            len + 1 - s_from - offs);
                                    memcpy(ctx->buf+offs, subs, s_to);
                                }
                                else {
                                    memcpy(ctx->buf + offs, subs, s_to);
                                    memmove(ctx->buf+offs+s_to,
                                            ctx->buf+offs+s_from,
                                            len + 1 - s_from - offs);
                                }
                            }
                        } else {
                            s_from = strlen(m->from.c);
                            if (!strncasecmp(ctx->buf, m->from.c, s_from)) {
                                ++num_match;
                                s_to = strlen(m->to);
                                len = strlen(ctx->buf);
                                VERBOSE(ap_log_rerror(APLOG_MARK, APLOG_TRACE3,
                                                      0, ctx->f->r,
                                              "H: matched %s, substituting %s",
                                                      m->from.c, m->to));
                                if (s_to > s_from) {
                                    preserve(ctx, s_to - s_from);
                                    memmove(ctx->buf+s_to, ctx->buf+s_from,
                                            len + 1 - s_from);
                                    memcpy(ctx->buf, m->to, s_to);
                                }
                                else {     /* it fits in the existing space */
                                    memcpy(ctx->buf, m->to, s_to);
                                    memmove(ctx->buf+s_to, ctx->buf+s_from,
                                            len + 1 - s_from);
                                }
                                break;
                            }
                        }
                        /* URIs only want one match unless overridden in the config */
                        if ((num_match > 0) && !(m->flags & M_NOTLAST))
                            break;
                    }
                    break;
                case ATTR_EVENT:
                    for (m = themap; m; m = m->next) {
                        num_match = 0;        /* reset here since we're working per-rule */
                        if (!(m->flags & M_EVENTS))
                            continue;
                        if (m->flags & M_REGEX) {
                            nmatch = 10;
                            offs = 0;
                            while (!ap_regexec(m->from.r, ctx->buf+offs,
                                               nmatch, pmatch, 0)) {
                                match = pmatch[0].rm_so;
                                s_from = pmatch[0].rm_eo - match;
                                subs = ap_pregsub(ctx->f->r->pool, m->to, ctx->buf+offs,
                                                    nmatch, pmatch);
                                VERBOSE({
                                    const char *f;
                                    f = apr_pstrndup(ctx->f->r->pool,
                                                     ctx->buf + offs, s_from);
                                    ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0,
                                                  ctx->f->r,
                                           "E/RX: match at %s, substituting %s",
                                                  f, subs);
                                })
                                s_to = strlen(subs);
                                offs += match;
                                len = strlen(ctx->buf);
                                if (s_to > s_from) {
                                    preserve(ctx, s_to - s_from);
                                    memmove(ctx->buf+offs+s_to,
                                            ctx->buf+offs+s_from,
                                            len + 1 - s_from - offs);
                                    memcpy(ctx->buf+offs, subs, s_to);
                                }
                                else {
                                    memcpy(ctx->buf + offs, subs, s_to);
                                    memmove(ctx->buf+offs+s_to,
                                            ctx->buf+offs+s_from,
                                            len + 1 - s_from - offs);
                                }
                                offs += s_to;
                                ++num_match;
                            }
                        }
                        else {
                            found = strstr(ctx->buf, m->from.c);
                            if ((m->flags & M_ATSTART) && (found != ctx->buf))
                                continue;
                            while (found) {
                                s_from = strlen(m->from.c);
                                s_to = strlen(m->to);
                                match = found - ctx->buf;
                                if ((s_from < strlen(found))
                                    && (m->flags & M_ATEND)) {
                                    found = strstr(ctx->buf+match+s_from,
                                                   m->from.c);
                                    continue;
                                }
                                else {
                                    found = strstr(ctx->buf+match+s_to,
                                                   m->from.c);
                                }
                                VERBOSE(ap_log_rerror(APLOG_MARK, APLOG_TRACE3,
                                                      0, ctx->f->r,
                                              "E: matched %s, substituting %s",
                                                      m->from.c, m->to));
                                len = strlen(ctx->buf);
                                if (s_to > s_from) {
                                    preserve(ctx, s_to - s_from);
                                    memmove(ctx->buf+match+s_to,
                                            ctx->buf+match+s_from,
                                            len + 1 - s_from - match);
                                    memcpy(ctx->buf+match, m->to, s_to);
                                }
                                else {
                                    memcpy(ctx->buf+match, m->to, s_to);
                                    memmove(ctx->buf+match+s_to,
                                            ctx->buf+match+s_from,
                                            len + 1 - s_from - match);
                                }
                                ++num_match;
                            }
                        }
                        if (num_match && (m->flags & M_LAST))
                            break;
                    }
                    break;
                case ATTR_IGNORE:
                    break;
                }
            }
            if (!a[1])
                ap_fputstrs(ctx->f->next, ctx->bb, " ", a[0], NULL);
            else {

                if (ctx->cfg->flags != 0)
                    normalise(ctx->cfg->flags, ctx->buf);

                /* write the attribute, using pcharacters to html-escape
                   anything that needs it in the value.
                */
                ap_fputstrs(ctx->f->next, ctx->bb, " ", a[0], "=\"", NULL);
                pcharacters(ctx, (const xmlChar*)ctx->buf, strlen(ctx->buf));
                ap_fputc(ctx->f->next, ctx->bb, '"');
            }
        }
    }
    ctx->offset = 0;
    if (desc && desc->empty)
        ap_fputs(ctx->f->next, ctx->bb, ctx->cfg->etag);
    else
        ap_fputc(ctx->f->next, ctx->bb, '>');

    if ((enforce > 0) && (required_attrs > 0)) {
        /* if there are more required attributes than we found then complain */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->f->r, APLOGNO(01420)
                      "HTML element %s is missing %d required attributes",
                      name, required_attrs);
    }
}