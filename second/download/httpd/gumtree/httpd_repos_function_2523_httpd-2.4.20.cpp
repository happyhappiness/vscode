void h2_request_copy(apr_pool_t *p, h2_request *dst, const h2_request *src)
{
    /* keep the dst id */
    dst->initiated_on   = src->initiated_on;
    dst->method         = OPT_COPY(p, src->method);
    dst->scheme         = OPT_COPY(p, src->scheme);
    dst->authority      = OPT_COPY(p, src->authority);
    dst->path           = OPT_COPY(p, src->path);
    dst->headers        = apr_table_clone(p, src->headers);
    if (src->trailers) {
        dst->trailers   = apr_table_clone(p, src->trailers);
    }
    else {
        dst->trailers   = NULL;
    }
    dst->content_length = src->content_length;
    dst->chunked        = src->chunked;
    dst->eoh            = src->eoh;
    dst->body           = src->body;
    dst->serialize      = src->serialize;
    dst->push_policy    = src->push_policy;
}