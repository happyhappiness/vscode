static apr_status_t impl_pollset_create(apr_pollset_t *pollset,
                                        apr_uint32_t size,
                                        apr_pool_t *p,
                                        apr_uint32_t flags)
{
    if (flags & APR_POLLSET_THREADSAFE) {                
        return APR_ENOTIMPL;
    }
#ifdef WIN32
    if (!APR_HAVE_LATE_DLL_FUNC(WSAPoll)) {
        return APR_ENOTIMPL;
    }
#endif
    pollset->p = apr_palloc(p, sizeof(apr_pollset_private_t));
    pollset->p->pollset = apr_palloc(p, size * sizeof(struct pollfd));
    pollset->p->query_set = apr_palloc(p, size * sizeof(apr_pollfd_t));
    pollset->p->result_set = apr_palloc(p, size * sizeof(apr_pollfd_t));

    return APR_SUCCESS;
}