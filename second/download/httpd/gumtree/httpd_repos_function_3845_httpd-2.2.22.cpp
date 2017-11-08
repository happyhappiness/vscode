static apr_status_t impl_pollset_remove(apr_pollset_t * pollset,
                                        const apr_pollfd_t * descriptor)
{
    apr_uint32_t i;
    apr_os_sock_t fd;

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        fd = descriptor->desc.s->socketdes;
    }
    else {
#if !APR_FILES_AS_SOCKETS
        return APR_EBADF;
#else
        fd = descriptor->desc.f->filedes;
#endif
    }

    for (i = 0; i < pollset->nelts; i++) {
        if (descriptor->desc.s == pollset->p->query_set[i].desc.s) {
            /* Found an instance of the fd: remove this and any other copies */
            apr_uint32_t dst = i;
            apr_uint32_t old_nelts = pollset->nelts;
            pollset->nelts--;
            for (i++; i < old_nelts; i++) {
                if (descriptor->desc.s == pollset->p->query_set[i].desc.s) {
                    pollset->nelts--;
                }
                else {
                    pollset->p->query_set[dst] = pollset->p->query_set[i];
                    dst++;
                }
            }
            FD_CLR(fd, &(pollset->p->readset));
            FD_CLR(fd, &(pollset->p->writeset));
            FD_CLR(fd, &(pollset->p->exceptset));
            if (((int) fd == pollset->p->maxfd) && (pollset->p->maxfd > 0)) {
                pollset->p->maxfd--;
            }
            return APR_SUCCESS;
        }
    }

    return APR_NOTFOUND;
}