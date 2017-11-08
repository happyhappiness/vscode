void h2_request_copy(apr_pool_t *p, h2_request *dst, const h2_request *src)
{
    /* keep the dst id */
    dst->method         = OPT_COPY(p, src->method);
    dst->scheme         = OPT_COPY(p, src->scheme);
    dst->authority      = OPT_COPY(p, src->authority);
    dst->path           = OPT_COPY(p, src->path);
    dst->headers        = apr_table_clone(p, src->headers);
    dst->content_length = src->content_length;
    dst->chunked        = src->chunked;
    dst->eoh            = src->eoh;
}