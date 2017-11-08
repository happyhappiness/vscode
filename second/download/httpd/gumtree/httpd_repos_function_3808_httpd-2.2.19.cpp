static apr_status_t impl_pollset_cleanup(apr_pollset_t *pollset)
{
    close(pollset->p->epoll_fd);
    return APR_SUCCESS;
}