static apr_pollset_provider_t *pollset_provider(apr_pollset_method_e method)
{
    apr_pollset_provider_t *provider = NULL;
    switch (method) {
        case APR_POLLSET_KQUEUE:
#if defined(HAVE_KQUEUE)
            provider = apr_pollset_provider_kqueue;
#endif
        break;
        case APR_POLLSET_PORT:
#if defined(HAVE_PORT_CREATE)
            provider = apr_pollset_provider_port;
#endif
        break;
        case APR_POLLSET_EPOLL:
#if defined(HAVE_EPOLL)
            provider = apr_pollset_provider_epoll;
#endif
        break;
        case APR_POLLSET_AIO_MSGQ:
#if defined(HAVE_AIO_MSGQ)
            provider = apr_pollset_provider_aio_msgq;
#endif
        break;
        case APR_POLLSET_POLL:
#if defined(HAVE_POLL)
            provider = apr_pollset_provider_poll;
#endif
        break;
        case APR_POLLSET_SELECT:
            provider = apr_pollset_provider_select;
        break;
        case APR_POLLSET_DEFAULT:
        break;
    }
    return provider;
}