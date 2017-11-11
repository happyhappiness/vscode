apr_status_t cache_generate_key_default( request_rec *r, apr_pool_t*p, char**key ) 
{
    if (r->hostname) {
        *key = apr_pstrcat(p, r->hostname, r->uri, "?", r->args, NULL);
    }
    else {
        *key = apr_pstrcat(p, r->uri, "?", r->args, NULL);
    }
    return APR_SUCCESS;
}