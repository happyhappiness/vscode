static void add_cookie(request_rec *r, char *s)
{
    char *var;
    char *val;
    char *domain;
    char *expires;
    char *path;
    char *secure;
    char *httponly;

    char *tok_cntx;
    char *cookie;

    var = apr_strtok(s, ":", &tok_cntx);
    val = apr_strtok(NULL, ":", &tok_cntx);
    domain = apr_strtok(NULL, ":", &tok_cntx);

    if (var && val && domain) {
        request_rec *rmain = r;
        char *notename;
        void *data;

        while (rmain->main) {
            rmain = rmain->main;
        }

        notename = apr_pstrcat(rmain->pool, var, "_rewrite", NULL);
        apr_pool_userdata_get(&data, notename, rmain->pool);
        if (!data) {
            char *exp_time = NULL;

            expires = apr_strtok(NULL, ":", &tok_cntx);
            path = expires ? apr_strtok(NULL, ":", &tok_cntx) : NULL;
            secure = path ? apr_strtok(NULL, ":", &tok_cntx) : NULL;
            httponly = secure ? apr_strtok(NULL, ":", &tok_cntx) : NULL;

            if (expires) {
                apr_time_exp_t tms;
                apr_time_exp_gmt(&tms, r->request_time
                                     + apr_time_from_sec((60 * atol(expires))));
                exp_time = apr_psprintf(r->pool, "%s, %.2d-%s-%.4d "
                                                 "%.2d:%.2d:%.2d GMT",
                                        apr_day_snames[tms.tm_wday],
                                        tms.tm_mday,
                                        apr_month_snames[tms.tm_mon],
                                        tms.tm_year+1900,
                                        tms.tm_hour, tms.tm_min, tms.tm_sec);
            }

            cookie = apr_pstrcat(rmain->pool,
                                 var, "=", val,
                                 "; path=", path ? path : "/",
                                 "; domain=", domain,
                                 expires ? "; expires=" : NULL,
                                 expires ? exp_time : NULL,
                                 (secure && (!strcasecmp(secure, "true")
                                             || !strcmp(secure, "1")
                                             || !strcasecmp(secure,
                                                            "secure"))) ?
                                  "; secure" : NULL,
                                 (httponly && (!strcasecmp(httponly, "true")
                                               || !strcmp(httponly, "1")
                                               || !strcasecmp(httponly,
                                                              "HttpOnly"))) ?
                                  "; HttpOnly" : NULL,
                                 NULL);

            apr_table_addn(rmain->err_headers_out, "Set-Cookie", cookie);
            apr_pool_userdata_set("set", notename, NULL, rmain->pool);
            rewritelog((rmain, 5, NULL, "setting cookie '%s'", cookie));
        }
        else {
            rewritelog((rmain, 5, NULL, "skipping already set cookie '%s'",
                        var));
        }
    }

    return;
}