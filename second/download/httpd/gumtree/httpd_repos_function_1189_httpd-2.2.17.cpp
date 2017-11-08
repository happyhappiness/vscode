static int apply_rewrite_cond(rewritecond_entry *p, rewrite_ctx *ctx)
{
    char *input = do_expand(p->input, ctx, NULL);
    apr_finfo_t sb;
    request_rec *rsub, *r = ctx->r;
    ap_regmatch_t regmatch[AP_MAX_REG_MATCH];
    int rc = 0;

    switch (p->ptype) {
    case CONDPAT_FILE_EXISTS:
        if (   apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS
            && sb.filetype == APR_REG) {
            rc = 1;
        }
        break;

    case CONDPAT_FILE_SIZE:
        if (   apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS
            && sb.filetype == APR_REG && sb.size > 0) {
            rc = 1;
        }
        break;

    case CONDPAT_FILE_LINK:
#if !defined(OS2)
        if (   apr_stat(&sb, input, APR_FINFO_MIN | APR_FINFO_LINK,
                        r->pool) == APR_SUCCESS
            && sb.filetype == APR_LNK) {
            rc = 1;
        }
#endif
        break;

    case CONDPAT_FILE_DIR:
        if (   apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS
            && sb.filetype == APR_DIR) {
            rc = 1;
        }
        break;

    case CONDPAT_FILE_XBIT:
        if (   apr_stat(&sb, input, APR_FINFO_PROT, r->pool) == APR_SUCCESS
            && (sb.protection & (APR_UEXECUTE | APR_GEXECUTE | APR_WEXECUTE))) {
            rc = 1;
        }
        break;

    case CONDPAT_LU_URL:
        if (*input && subreq_ok(r)) {
            rsub = ap_sub_req_lookup_uri(input, r, NULL);
            if (rsub->status < 400) {
                rc = 1;
            }
            rewritelog((r, 5, NULL, "RewriteCond URI (-U) check: "
                        "path=%s -> status=%d", input, rsub->status));
            ap_destroy_sub_req(rsub);
        }
        break;

    case CONDPAT_LU_FILE:
        if (*input && subreq_ok(r)) {
            rsub = ap_sub_req_lookup_file(input, r, NULL);
            if (rsub->status < 300 &&
                /* double-check that file exists since default result is 200 */
                apr_stat(&sb, rsub->filename, APR_FINFO_MIN,
                         r->pool) == APR_SUCCESS) {
                rc = 1;
            }
            rewritelog((r, 5, NULL, "RewriteCond file (-F) check: path=%s "
                        "-> file=%s status=%d", input, rsub->filename,
                        rsub->status));
            ap_destroy_sub_req(rsub);
        }
        break;

    case CONDPAT_STR_GT:
        rc = (compare_lexicography(input, p->pattern+1) == 1) ? 1 : 0;
        break;

    case CONDPAT_STR_LT:
        rc = (compare_lexicography(input, p->pattern+1) == -1) ? 1 : 0;
        break;

    case CONDPAT_STR_EQ:
        if (p->flags & CONDFLAG_NOCASE) {
            rc = !strcasecmp(input, p->pattern);
        }
        else {
            rc = !strcmp(input, p->pattern);
        }
        break;

    default:
        /* it is really a regexp pattern, so apply it */
        rc = !ap_regexec(p->regexp, input, AP_MAX_REG_MATCH, regmatch, 0);

        /* update briRC backref info */
        if (rc && !(p->flags & CONDFLAG_NOTMATCH)) {
            ctx->briRC.source = input;
            ctx->briRC.nsub   = p->regexp->re_nsub;
            memcpy(ctx->briRC.regmatch, regmatch, sizeof(regmatch));
        }
        break;
    }

    if (p->flags & CONDFLAG_NOTMATCH) {
        rc = !rc;
    }

    rewritelog((r, 4, ctx->perdir, "RewriteCond: input='%s' pattern='%s%s%s'%s "
                "=> %s", input, (p->flags & CONDFLAG_NOTMATCH) ? "!" : "",
                (p->ptype == CONDPAT_STR_EQ) ? "=" : "", p->pattern,
                (p->flags & CONDFLAG_NOCASE) ? " [NC]" : "",
                rc ? "matched" : "not-matched"));

    return rc;
}