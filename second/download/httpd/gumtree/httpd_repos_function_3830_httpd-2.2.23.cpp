static apr_status_t impl_pollcb_create(apr_pollcb_t *pollcb,
                                       apr_uint32_t size,
                                       apr_pool_t *p,
                                       apr_uint32_t flags)
{
#if APR_HAS_THREADS
    return APR_ENOTIMPL;
#else
    pollcb->fd = -1;
#ifdef WIN32
    if (!APR_HAVE_LATE_DLL_FUNC(WSAPoll)) {
        return APR_ENOTIMPL;
    }
#endif

    pollcb->pollset.ps = apr_palloc(p, size * sizeof(struct pollfd));
    pollcb->copyset = apr_palloc(p, size * sizeof(apr_pollfd_t *));

    return APR_SUCCESS;
#endif
}