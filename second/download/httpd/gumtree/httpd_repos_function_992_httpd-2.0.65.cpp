static int apply_rewrite_cond(request_rec *r, rewritecond_entry *p,
                              char *perdir, backrefinfo *briRR,
                              backrefinfo *briRC)
{
    char input[MAX_STRING_LEN];
    apr_finfo_t sb;
    request_rec *rsub;
    regmatch_t regmatch[AP_MAX_REG_MATCH];
    int rc;

    /*
     *   Construct the string we match against
     */

    do_expand(r, p->input, input, sizeof(input), briRR, briRC);

    /*
     *   Apply the patterns
     */

    rc = 0;
    if (strcmp(p->pattern, "-f") == 0) {
        if (apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS) {
            if (sb.filetype == APR_REG) {
                rc = 1;
            }
        }
    }
    else if (strcmp(p->pattern, "-s") == 0) {
        if (apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS) {
            if ((sb.filetype == APR_REG) && sb.size > 0) {
                rc = 1;
            }
        }
    }
    else if (strcmp(p->pattern, "-l") == 0) {
#if !defined(OS2)
        if (apr_lstat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS) {
            if (sb.filetype == APR_LNK) {
                rc = 1;
            }
        }
#endif
    }
    else if (strcmp(p->pattern, "-d") == 0) {
        if (apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS) {
            if (sb.filetype == APR_DIR) {
                rc = 1;
            }
        }
    }
    else if (strcmp(p->pattern, "-U") == 0) {
        /* avoid infinite subrequest recursion */
        if (strlen(input) > 0 && subreq_ok(r)) {

            /* run a URI-based subrequest */
            rsub = ap_sub_req_lookup_uri(input, r, NULL);

            /* URI exists for any result up to 3xx, redirects allowed */
            if (rsub->status < 400)
                rc = 1;

            /* log it */
            rewritelog(r, 5, "RewriteCond URI (-U) check: "
                       "path=%s -> status=%d", input, rsub->status);

            /* cleanup by destroying the subrequest */
            ap_destroy_sub_req(rsub);
        }
    }
    else if (strcmp(p->pattern, "-F") == 0) {
        /* avoid infinite subrequest recursion */
        if (strlen(input) > 0 && subreq_ok(r)) {

            /* process a file-based subrequest:
             * this differs from -U in that no path translation is done.
             */
            rsub = ap_sub_req_lookup_file(input, r, NULL);

            /* file exists for any result up to 2xx, no redirects */
            if (rsub->status < 300 &&
                /* double-check that file exists since default result is 200 */
                apr_stat(&sb, rsub->filename, APR_FINFO_MIN,
                         r->pool) == APR_SUCCESS) {
                rc = 1;
            }

            /* log it */
            rewritelog(r, 5, "RewriteCond file (-F) check: path=%s "
                       "-> file=%s status=%d", input, rsub->filename,
                       rsub->status);

            /* cleanup by destroying the subrequest */
            ap_destroy_sub_req(rsub);
        }
    }
    else if (strlen(p->pattern) > 1 && *(p->pattern) == '>') {
        rc = (compare_lexicography(input, p->pattern+1) == 1 ? 1 : 0);
    }
    else if (strlen(p->pattern) > 1 && *(p->pattern) == '<') {
        rc = (compare_lexicography(input, p->pattern+1) == -1 ? 1 : 0);
    }
    else if (strlen(p->pattern) > 1 && *(p->pattern) == '=') {
        if (strcmp(p->pattern+1, "\"\"") == 0) {
            rc = (*input == '\0');
        }
        else {
            rc = (strcmp(input, p->pattern+1) == 0 ? 1 : 0);
        }
    }
    else {
        /* it is really a regexp pattern, so apply it */
        rc = (ap_regexec(p->regexp, input, AP_MAX_REG_MATCH, regmatch,0) == 0);

        /* if it isn't a negated pattern and really matched
           we update the passed-through regex subst info structure */
        if (rc && !(p->flags & CONDFLAG_NOTMATCH)) {
            briRC->source = apr_pstrdup(r->pool, input);
            briRC->nsub   = p->regexp->re_nsub;
            memcpy((void *)(briRC->regmatch), (void *)(regmatch),
                   sizeof(regmatch));
        }
    }

    /* if this is a non-matching regexp, just negate the result */
    if (p->flags & CONDFLAG_NOTMATCH) {
        rc = !rc;
    }

    rewritelog(r, 4, "RewriteCond: input='%s' pattern='%s%s' => %s",
               input, (p->flags & CONDFLAG_NOTMATCH ? "!" : ""),
               p->pattern, rc ? "matched" : "not-matched");

    /* end just return the result */
    return rc;
}