static apr_array_header_t *proxy_vars(request_rec *r,
                                      apr_array_header_t *hdr)
{
    int i;
    apr_array_header_t *ret = apr_array_make(r->pool, hdr->nelts,
                                             sizeof (struct proxy_alias));
    struct proxy_alias *old = (struct proxy_alias *) hdr->elts;

    for (i = 0; i < hdr->nelts; ++i) {
        struct proxy_alias *newcopy = apr_array_push(ret);
        newcopy->fake = (old[i].flags & PROXYPASS_INTERPOLATE)
                        ? proxy_interpolate(r, old[i].fake) : old[i].fake;
        newcopy->real = (old[i].flags & PROXYPASS_INTERPOLATE)
                        ? proxy_interpolate(r, old[i].real) : old[i].real;
    }
    return ret;
}