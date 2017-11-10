apr_status_t apr_socket_sendfile(apr_socket_t *sock, apr_file_t *file,
                                 apr_hdtr_t *hdtr, apr_off_t *offset,
                                 apr_size_t *len, apr_int32_t flags)
{
    off_t off = *offset;
    int rv, nbytes = 0, total_hdrbytes, i;
    apr_status_t arv;

    if (!hdtr) {
        hdtr = &no_hdtr;
    }

    /* Ignore flags for now. */
    flags = 0;

    if (hdtr->numheaders > 0) {
        apr_size_t hdrbytes;

        /* cork before writing headers */
        rv = apr_socket_opt_set(sock, APR_TCP_NOPUSH, 1);
        if (rv != APR_SUCCESS) {
            return rv;
        }

        /* Now write the headers */
        arv = apr_socket_sendv(sock, hdtr->headers, hdtr->numheaders,
                               &hdrbytes);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return errno;
        }
        nbytes += hdrbytes;

        /* If this was a partial write and we aren't doing timeouts, 
         * return now with the partial byte count; this is a non-blocking 
         * socket.
         */
        total_hdrbytes = 0;
        for (i = 0; i < hdtr->numheaders; i++) {
            total_hdrbytes += hdtr->headers[i].iov_len;
        }
        if (hdrbytes < total_hdrbytes) {
            *len = hdrbytes;
            return apr_socket_opt_set(sock, APR_TCP_NOPUSH, 0);
        }
    }

    if (sock->netmask & APR_INCOMPLETE_WRITE) {
        sock->netmask &= ~APR_INCOMPLETE_WRITE;
        goto do_select;
    }

    do {
        rv = sendfile(sock->socketdes,    /* socket */
                      file->filedes, /* open file descriptor of the file to be sent */
                      &off,    /* where in the file to start */
                      *len);   /* number of bytes to send */
    } while (rv == -1 && errno == EINTR);

    while (rv == -1 && 
        (errno == EAGAIN || errno == EWOULDBLOCK) && 
        apr_is_option_set(sock->netmask, APR_SO_TIMEOUT)) {
do_select:
        arv = apr_wait_for_io_or_timeout(NULL, sock, 0);
        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        }
        else {
            do {
                rv = sendfile(sock->socketdes,    /* socket */
                              file->filedes, /* open file descriptor of the file to be sent */
                              &off,    /* where in the file to start */
                              *len);    /* number of bytes to send */
            } while (rv == -1 && errno == EINTR);
        }
    }

    if (rv == -1) {
        *len = nbytes;
        rv = errno;
        apr_socket_opt_set(sock, APR_TCP_NOPUSH, 0);
        return rv;
    }

    nbytes += rv;

    if (rv < *len) {
        *len = nbytes;
        arv = apr_socket_opt_set(sock, APR_TCP_NOPUSH, 0);
        if (rv > 0) {
                
            /* If this was a partial write, return now with the 
             * partial byte count;  this is a non-blocking socket.
             */

            if (apr_is_option_set(sock->netmask, APR_SO_TIMEOUT)) {
                sock->netmask |= APR_INCOMPLETE_WRITE;
            }
            return arv;
        }
        else {
            /* If the file got smaller mid-request, eventually the offset
             * becomes equal to the new file size and the kernel returns 0.  
             * Make this an error so the caller knows to log something and
             * exit.
             */
            return APR_EOF;
        }
    }

    /* Now write the footers */
    if (hdtr->numtrailers > 0) {
        apr_size_t trbytes;
        arv = apr_socket_sendv(sock, hdtr->trailers, hdtr->numtrailers, 
                               &trbytes);
        nbytes += trbytes;
        if (arv != APR_SUCCESS) {
            *len = nbytes;
            rv = errno;
            apr_socket_opt_set(sock, APR_TCP_NOPUSH, 0);
            return rv;
        }
    }

    apr_socket_opt_set(sock, APR_TCP_NOPUSH, 0);
    
    (*len) = nbytes;
    return rv < 0 ? errno : APR_SUCCESS;
}