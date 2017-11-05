static int handler_redirect(request_rec *r)
{
    if (strcmp(r->handler, "redirect-handler")) {
        return DECLINED;
    }

    /* just make sure that we are really meant! */
    if (strncmp(r->filename, "redirect:", 9) != 0) {
        return DECLINED;
    }

    if (is_redirect_limit_exceeded(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "mod_rewrite: maximum number of internal redirects "
                      "reached. Assuming configuration error. Use "
                      "'RewriteOptions MaxRedirects' to increase the limit "
                      "if neccessary.");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* now do the internal redirect */
    ap_internal_redirect(apr_pstrcat(r->pool, r->filename+9,
                                     r->args ? "?" : NULL, r->args, NULL), r);

    /* and return gracefully */
    return OK;
}