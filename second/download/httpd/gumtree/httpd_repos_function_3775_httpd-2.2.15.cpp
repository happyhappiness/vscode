static apr_pollcb_provider_t *pollcb_provider(apr_pollset_method_e method)
{
    apr_pollcb_provider_t *provider = NULL;
    switch (method) {
        case APR_POLLSET_KQUEUE:
#if defined(HAVE_KQUEUE)
            provider = apr_pollcb_provider_kqueue;
#endif
        break;
        case APR_POLLSET_PORT:
#if defined(HAVE_PORT_CREATE)
            provider = apr_pollcb_provider_port;
#endif
        break;
        case APR_POLLSET_EPOLL:
#if defined(HAVE_EPOLL)
            provider = apr_pollcb_provider_epoll;
#endif
        break;
        case APR_POLLSET_POLL:
#if defined(HAVE_POLL)
            provider = apr_pollcb_provider_poll;
#endif
        break;
        case APR_POLLSET_SELECT:
        case APR_POLLSET_DEFAULT:
        break;
    }
    return provider;
}