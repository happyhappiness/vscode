    return DECLINED;
}

apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
                                        char**key)
{
    char *port_str, *hn, *lcs;
    const char *hostname, *scheme;
    int i;

    /*
     * Use the canonical name to improve cache hit rate, but only if this is
     * not a proxy request or if this is a reverse proxy request.
     * We need to handle both cases in the same manner as for the reverse proxy
     * case we have the following situation:
     *
