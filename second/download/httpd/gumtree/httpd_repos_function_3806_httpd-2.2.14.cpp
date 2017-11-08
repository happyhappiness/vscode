apr_status_t apr_socket_sendfile(apr_socket_t *sock, apr_file_t *file,
                                 apr_hdtr_t *hdtr, apr_off_t *offset,
                                 apr_size_t *len, apr_int32_t flags)
{
    apr_status_t rv, arv;
    apr_size_t nbytes;
    sendfilevec_t *sfv;
    int vecs, curvec, i, repeat;
    apr_size_t requested_len = 0;

    if (!hdtr) {
        hdtr = &no_hdtr;
    }

    /* Ignore flags for now. */
    flags = 0;

    /* Calculate how much space we need. */
    vecs = hdtr->numheaders + hdtr->numtrailers + 1;
    sfv = apr_palloc(sock->pool, sizeof(sendfilevec_t) * vecs);

    curvec = 0;

    /* Add the headers */
    for (i = 0; i < hdtr->numheaders; i++, curvec++) {
        sfv[curvec].sfv_fd = SFV_FD_SELF;
        sfv[curvec].sfv_flag = 0;
        /* Cast to unsigned long to prevent sign extension of the
         * pointer value for the LFS case; see PR 39463. */
        sfv[curvec].sfv_off = (unsigned long)hdtr->headers[i].iov_base;
        sfv[curvec].sfv_len = hdtr->headers[i].iov_len;
        requested_len += sfv[curvec].sfv_len;
    }

    /* If the len is 0, we skip the file. */
    if (*len)
    {
        sfv[curvec].sfv_fd = file->filedes;
        sfv[curvec].sfv_flag = 0;
        sfv[curvec].sfv_off = *offset;
        sfv[curvec].sfv_len = *len; 
        requested_len += sfv[curvec].sfv_len;

        curvec++;
    }
    else {
        vecs--;
    }

    /* Add the footers */
    for (i = 0; i < hdtr->numtrailers; i++, curvec++) {
        sfv[curvec].sfv_fd = SFV_FD_SELF;
        sfv[curvec].sfv_flag = 0;
        sfv[curvec].sfv_off = (unsigned long)hdtr->trailers[i].iov_base;
        sfv[curvec].sfv_len = hdtr->trailers[i].iov_len;
        requested_len += sfv[curvec].sfv_len;
    }

    /* If the last write couldn't send all the requested data,
     * wait for the socket to become writable before proceeding
     */
    if (sock->options & APR_INCOMPLETE_WRITE) {
        sock->options &= ~APR_INCOMPLETE_WRITE;
        arv = apr_wait_for_io_or_timeout(NULL, sock, 0);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        }
    }
 
    /* Actually do the sendfilev
     *
     * Solaris may return -1/EAGAIN even if it sent bytes on a non-block sock.
     *
     * If no bytes were originally sent (nbytes == 0) and we are on a TIMEOUT 
     * socket (which as far as the OS is concerned is a non-blocking socket), 
     * we want to retry after waiting for the other side to read the data (as 
     * determined by poll).  Once it is clear to send, we want to retry
     * sending the sendfilevec_t once more.
     */
    arv = 0;
    do {
        /* Clear out the repeat */
        repeat = 0;

        /* socket, vecs, number of vecs, bytes written */
        rv = sendfilev(sock->socketdes, sfv, vecs, &nbytes);

        if (rv == -1 && errno == EAGAIN) {
            if (nbytes) {
                rv = 0;
            }
            else if (!arv && (sock->timeout > 0)) {
                apr_status_t t = apr_wait_for_io_or_timeout(NULL, sock, 0);

                if (t != APR_SUCCESS) {
                    *len = 0;
                    return t;
                }

                arv = 1; 
                repeat = 1;
            }
        }
    } while ((rv == -1 && errno == EINTR) || repeat);

    if (rv == -1) {
        *len = 0;
        return errno;
    }

    /* Update how much we sent */
    *len = nbytes;

    if (nbytes == 0) {
        /* Most likely the file got smaller after the stat.
         * Return an error so the caller can do the Right Thing.
         */
        return APR_EOF;
    }

    if ((sock->timeout > 0) && (*len < requested_len)) {
        sock->options |= APR_INCOMPLETE_WRITE;
    }
    return APR_SUCCESS;
}