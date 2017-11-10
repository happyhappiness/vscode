static apr_status_t impl_pollset_create(apr_pollset_t *pollset,
                                        apr_uint32_t size,
                                        apr_pool_t *p,
                                        apr_uint32_t flags)
{
    if (flags & APR_POLLSET_THREADSAFE) {                
        pollset->p = NULL;
        return APR_ENOTIMPL;
    }
#ifdef FD_SETSIZE
    if (size > FD_SETSIZE) {
        pollset->p = NULL;
        return APR_EINVAL;
    }
#endif
    pollset->p = apr_palloc(p, sizeof(apr_pollset_private_t));
    FD_ZERO(&(pollset->p->readset));
    FD_ZERO(&(pollset->p->writeset));
    FD_ZERO(&(pollset->p->exceptset));
    pollset->p->maxfd = 0;
#ifdef NETWARE
    pollset->p->set_type = APR_NO_DESC;
#endif
    pollset->p->query_set = apr_palloc(p, size * sizeof(apr_pollfd_t));
    pollset->p->result_set = apr_palloc(p, size * sizeof(apr_pollfd_t));

    return APR_SUCCESS;
}