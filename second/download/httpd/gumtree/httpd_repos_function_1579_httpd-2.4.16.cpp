static int apply_rewrite_cond(rewritecond_entry *p, rewrite_ctx *ctx)
{
    char *input = NULL;
    apr_finfo_t sb;
    request_rec *rsub, *r = ctx->r;
    ap_regmatch_t regmatch[AP_MAX_REG_MATCH];
    int rc = 0;
    int basis;

    if (p->ptype != CONDPAT_AP_EXPR)
        input = do_expand(p->input, ctx, NULL);

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

    case CONDPAT_STR_GE:
        basis = 0;
        goto test_str_g;
    case CONDPAT_STR_GT:
        basis = 1;
test_str_g:
        if (p->flags & CONDFLAG_NOCASE) {
            rc = (strcasecmp(input, p->pattern) >= basis) ? 1 : 0;
        }
        else {
            rc = (compare_lexicography(input, p->pattern) >= basis) ? 1 : 0;
        }
        break;

    case CONDPAT_STR_LE:
        basis = 0;
        goto test_str_l;
    case CONDPAT_STR_LT:
        basis = -1;
test_str_l:
        if (p->flags & CONDFLAG_NOCASE) {
            rc = (strcasecmp(input, p->pattern) <= basis) ? 1 : 0;
        }
        else {
            rc = (compare_lexicography(input, p->pattern) <= basis) ? 1 : 0;
        }
        break;

    case CONDPAT_STR_EQ:
        /* Note: the only type where the operator is dropped from p->pattern */
        if (p->flags & CONDFLAG_NOCASE) {
            rc = !strcasecmp(input, p->pattern);
        }
        else {
            rc = !strcmp(input, p->pattern);
        }
        break;

    case CONDPAT_INT_GE: rc = (atoi(input) >= atoi(p->pattern)); break;
    case CONDPAT_INT_GT: rc = (atoi(input) > atoi(p->pattern));  break;

    case CONDPAT_INT_LE: rc = (atoi(input) <= atoi(p->pattern)); break;
    case CONDPAT_INT_LT: rc = (atoi(input) < atoi(p->pattern));  break;

    case CONDPAT_INT_EQ: rc = (atoi(input) == atoi(p->pattern)); break;

    case CONDPAT_AP_EXPR:
        {
            const char *err, *source;
            rc = ap_expr_exec_re(r, p->expr, AP_MAX_REG_MATCH, regmatch,
                                 &source, &err);
            if (rc < 0 || err) {
                rewritelog((r, 1, ctx->perdir,
                            "RewriteCond: expr='%s' evaluation failed: %s",
                            p->pattern - p->pskip, err));
                rc = 0;
            }
            /* update briRC backref info */
            if (rc && !(p->flags & CONDFLAG_NOTMATCH)) {
                ctx->briRC.source = source;
                memcpy(ctx->briRC.regmatch, regmatch, sizeof(regmatch));
            }
        }
        break;
    default:
        /* it is really a regexp pattern, so apply it */
        rc = !ap_regexec(p->regexp, input, AP_MAX_REG_MATCH, regmatch, 0);

        /* update briRC backref info */
        if (rc && !(p->flags & CONDFLAG_NOTMATCH)) {
            ctx->briRC.source = input;
            memcpy(ctx->briRC.regmatch, regmatch, sizeof(regmatch));
        }
        break;
    }

    if (p->flags & CONDFLAG_NOTMATCH) {
        rc = !rc;
    }

    rewritelog((r, 4, ctx->perdir, "RewriteCond: input='%s' pattern='%s'%s "
                "=> %s", input, p->pattern - p->pskip,
                (p->flags & CONDFLAG_NOCASE) ? " [NC]" : "",
                rc ? "matched" : "not-matched"));

    return rc;
}