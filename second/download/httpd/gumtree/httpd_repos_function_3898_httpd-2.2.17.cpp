apr_status_t apr_socket_sendfile(apr_socket_t *sock, apr_file_t *file,
                                 apr_hdtr_t *hdtr, apr_off_t *offset,
                                 apr_size_t *len, apr_int32_t flags)
{
    apr_off_t nbytes = 0;
    apr_off_t bytes_to_send = *len;
    apr_off_t bytes_sent = 0;
    apr_status_t arv;
    int rv = 0;

    /* Ignore flags for now. */
    flags = 0;

    if (!hdtr) {
        hdtr = &no_hdtr;
    }

    /* OS X can send the headers/footers as part of the system call, 
     * but how it counts bytes isn't documented properly. We use 
     * apr_socket_sendv() instead.
     */
     if (hdtr->numheaders > 0) {
        apr_size_t hbytes;
        int i;

        /* Now write the headers */
        arv = apr_socket_sendv(sock, hdtr->headers, hdtr->numheaders,
                               &hbytes);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return errno;
        }
        bytes_sent = hbytes;

        hbytes = 0;
        for (i = 0; i < hdtr->numheaders; i++) {
            hbytes += hdtr->headers[i].iov_len;
        }
        if (bytes_sent < hbytes) {
            *len = bytes_sent;
            return APR_SUCCESS;
        }
    }

    do {
        if (!bytes_to_send) {
            break;
        }
        if (sock->options & APR_INCOMPLETE_WRITE) {
            apr_status_t arv;
            sock->options &= ~APR_INCOMPLETE_WRITE;
            arv = apr_wait_for_io_or_timeout(NULL, sock, 0);
            if (arv != APR_SUCCESS) {
                *len = 0;
                return arv;
            }
        }

        nbytes = bytes_to_send;
        rv = sendfile(file->filedes, /* file to be sent */
                      sock->socketdes, /* socket */
                      *offset,       /* where in the file to start */
                      &nbytes,       /* number of bytes to write/written */
                      NULL,          /* Headers/footers */
                      flags);        /* undefined, set to 0 */

        if (rv == -1) {
            if (errno == EAGAIN) {
                if (sock->timeout > 0) {
                    sock->options |= APR_INCOMPLETE_WRITE;
                }
                /* BSD's sendfile can return -1/EAGAIN even if it
                 * sent bytes.  Sanitize the result so we get normal EAGAIN
                 * semantics w.r.t. bytes sent.
                 */
                if (nbytes) {
                    bytes_sent += nbytes;
                    /* normal exit for a big file & non-blocking io */
                    (*len) = bytes_sent;
                    return APR_SUCCESS;
                }
            }
        }
        else {       /* rv == 0 (or the kernel is broken) */
            bytes_sent += nbytes;
            if (nbytes == 0) {
                /* Most likely the file got smaller after the stat.
                 * Return an error so the caller can do the Right Thing.
                 */
                (*len) = bytes_sent;
                return APR_EOF;
            }
        }
    } while (rv == -1 && (errno == EINTR || errno == EAGAIN));

    /* Now write the footers */
    if (hdtr->numtrailers > 0) {
        apr_size_t tbytes;
        arv = apr_socket_sendv(sock, hdtr->trailers, hdtr->numtrailers, 
                               &tbytes);
        bytes_sent += tbytes;
        if (arv != APR_SUCCESS) {
            *len = bytes_sent;
            rv = errno;
            return rv;
        }
    }

    (*len) = bytes_sent;
    if (rv == -1) {
        return errno;
    }
    return APR_SUCCESS;
}