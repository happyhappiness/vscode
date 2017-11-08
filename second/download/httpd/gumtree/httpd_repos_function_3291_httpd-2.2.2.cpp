apr_status_t apr_wait_for_io_or_timeout(apr_file_t *f, apr_socket_t *s,
                                        int for_read)
{
    apr_interval_time_t timeout;
    apr_pollfd_t pfd;
    int type = for_read ? APR_POLLIN : APR_POLLOUT;
    apr_pollset_t *pollset;
    apr_status_t status;

    /* TODO - timeout should be less each time through this loop */
    if (f) {
        pfd.desc_type = APR_POLL_FILE;
        pfd.desc.f = f;

        pollset = f->pollset;
        if (pollset == NULL) {
            status = apr_pollset_create(&(f->pollset), 1, f->pool, 0);
            if (status != APR_SUCCESS) {
                return status;
            }
            pollset = f->pollset;
        }
        timeout = f->timeout;
    }
    else {
        pfd.desc_type = APR_POLL_SOCKET;
        pfd.desc.s = s;

        pollset = s->pollset;
        timeout = s->timeout;
    }
    pfd.reqevents = type;

    /* Remove the object if it was in the pollset, then add in the new
     * object with the correct reqevents value. Ignore the status result
     * on the remove, because it might not be in there (yet).
     */
    (void) apr_pollset_remove(pollset, &pfd);

    /* ### check status code */
    (void) apr_pollset_add(pollset, &pfd);

    do {
        int numdesc;
        const apr_pollfd_t *pdesc;

        status = apr_pollset_poll(pollset, timeout, &numdesc, &pdesc);

        if (numdesc == 1 && (pdesc[0].rtnevents & type) != 0) {
            return APR_SUCCESS;
        }
    } while (APR_STATUS_IS_EINTR(status));

    return status;
}