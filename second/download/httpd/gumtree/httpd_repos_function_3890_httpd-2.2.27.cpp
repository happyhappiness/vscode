static apr_status_t cb_cleanup(void *b_)
{
    apr_pollcb_t *pollcb = (apr_pollcb_t *) b_;
    close(pollcb->fd);
    return APR_SUCCESS;
}