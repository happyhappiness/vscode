static void create_hcheck_req(wctx_t *wctx, proxy_worker *hc,
                              apr_pool_t *p)
{
    char *req = NULL;
    const char *method = NULL;
    switch (hc->s->method) {
        case OPTIONS:
            method = "OPTIONS";
            req = apr_psprintf(p,
                               "OPTIONS * HTTP/1.0\r\n"
                               "Host: %s:%d\r\n"
                               "\r\n",
                               hc->s->hostname, (int)hc->s->port);
            break;

        case HEAD:
            method = "HEAD";
            /* fallthru */
        case GET:
            if (!method) { /* did we fall thru? If not, we are GET */
                method = "GET";
            }
            req = apr_psprintf(p,
                               "%s %s%s%s HTTP/1.0\r\n"
                               "Host: %s:%d\r\n"
                               "\r\n",
                               method,
                               (wctx->path ? wctx->path : ""),
                               (wctx->path && *hc->s->hcuri ? "/" : "" ),
                               (*hc->s->hcuri ? hc->s->hcuri : ""),
                               hc->s->hostname, (int)hc->s->port);
            break;

        default:
            break;
    }
    wctx->req = req;
    wctx->method = method;
}