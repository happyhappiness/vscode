static void add_cookie(request_rec *r, char *s)
{
    char *var;
    char *val;
    char *domain;
    char *expires;
    char *path;

    char *tok_cntx;
    char *cookie;

    if (s) {
        var = apr_strtok(s, ":", &tok_cntx);
        val = apr_strtok(NULL, ":", &tok_cntx);
        domain = apr_strtok(NULL, ":", &tok_cntx);
        /** the line below won't hit the token ever **/
        expires = apr_strtok(NULL, ":", &tok_cntx);
        if (expires) {
            path = apr_strtok(NULL,":", &tok_cntx);
        }
        else {
            path = NULL;
        }

        if (var && val && domain) {
            /* FIX: use cached time similar to how logging does it */
            request_rec *rmain = r;
            char *notename;
            void *data;
            while (rmain->main) {
                rmain = rmain->main;
            }

            notename = apr_pstrcat(rmain->pool, var, "_rewrite", NULL);
            apr_pool_userdata_get(&data, notename, rmain->pool);
            if (data == NULL) {
                cookie = apr_pstrcat(rmain->pool,
                                     var, "=", val,
                                     "; path=", (path)? path : "/",
                                     "; domain=", domain,
                                     (expires)? "; expires=" : NULL,
                                     (expires)?
                                     ap_ht_time(r->pool,
                                                r->request_time +
                                                apr_time_from_sec((60 *
                                                               atol(expires))),
                                                "%a, %d-%b-%Y %T GMT", 1)
                                              : NULL,
                                     NULL);
                /*
                 * XXX: should we add it to err_headers_out as well ?
                 * if we do we need to be careful that only ONE gets sent out
                 */
                apr_table_add(rmain->err_headers_out, "Set-Cookie", cookie);
                apr_pool_userdata_set("set", notename, NULL, rmain->pool);
                rewritelog(rmain, 5, "setting cookie '%s'", cookie);
            }
            else {
                rewritelog(rmain, 5, "skipping already set cookie '%s'", var);
            }
        }
    }
}