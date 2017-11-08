h2_request *h2_request_clone(apr_pool_t *p, const h2_request *src)
{
    h2_request *nreq = apr_pcalloc(p, sizeof(*nreq));
    memcpy(nreq, src, sizeof(*nreq));
    h2_request_copy(p, nreq, src);
    return nreq;
}