static int add_push(link_ctx *ctx)
{
    /* so, we have read a Link header and need to decide
     * if we transform it into a push.
     */
    const char *rel = apr_table_get(ctx->params, "rel");
    if (rel && !strcmp("preload", rel)) {
        apr_uri_t uri;
        if (apr_uri_parse(ctx->pool, ctx->link, &uri) == APR_SUCCESS) {
            if (uri.path && same_authority(ctx->req, &uri)) {
                char *path;
                apr_table_t *headers;
                h2_request *req;
                h2_push *push;
                
                /* We only want to generate pushes for resources in the
                 * same authority than the original request.
                 * icing: i think that is wise, otherwise we really need to
                 * check that the vhost/server is available and uses the same
                 * TLS (if any) parameters.
                 */
                path = apr_uri_unparse(ctx->pool, &uri, APR_URI_UNP_OMITSITEPART);
                
                push = apr_pcalloc(ctx->pool, sizeof(*push));
                
                headers = apr_table_make(ctx->pool, 5);
                apr_table_do(set_header, headers, ctx->req->headers,
                             "User-Agent",
                             "Cache-Control",
                             "Accept-Language",
                             NULL);
                req = h2_request_createn(0, ctx->pool, ctx->req->config, 
                                         "GET", ctx->req->scheme,
                                         ctx->req->authority, 
                                         path, headers);
                h2_request_end_headers(req, ctx->pool, 1);
                push->req = req;
                
                if (!ctx->pushes) {
                    ctx->pushes = apr_array_make(ctx->pool, 5, sizeof(h2_push*));
                }
                APR_ARRAY_PUSH(ctx->pushes, h2_push*) = push;
            }
        }
    }
    return 0;
}