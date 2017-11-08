static void *proxy_html_config(apr_pool_t *pool, char *x)
{
    proxy_html_conf *ret = apr_pcalloc(pool, sizeof(proxy_html_conf));
    ret->doctype = DEFAULT_DOCTYPE;
    ret->etag = DEFAULT_ETAG;
    ret->bufsz = 8192;
    /* ret->interp = 1; */
    /* don't initialise links and events until they get set/used */
    return ret;
}