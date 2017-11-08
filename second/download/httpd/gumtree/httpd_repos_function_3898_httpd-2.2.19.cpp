apr_status_t apr_socket_sendfile(apr_socket_t *sock, apr_file_t *file,
                                 apr_hdtr_t *hdtr, apr_off_t *offset,
                                 apr_size_t *len, apr_int32_t flags)
{
    int rv, nbytes = 0, total_hdrbytes, i;
    apr_status_t arv;

#if APR_HAS_LARGE_FILES && defined(HAVE_SENDFILE64)
    apr_off_t off = *offset;
#define sendfile sendfile64

#elif APR_HAS_LARGE_FILES && SIZEOF_OFF_T == 4
    /* 64-bit apr_off_t but no sendfile64(): fail if trying to send
     * past the 2Gb limit. */
    off_t off;
    
    if ((apr_int64_t)*offset + *len > INT_MAX) {
        return EINVAL;
    }
    
    off = *offset;

#else
    off_t off = *offset;

    /* Multiple reports have shown sendfile failing with EINVAL if
     * passed a >=2Gb count value on some 64-bit kernels.  It won't
     * noticably hurt performance to limit each call to <2Gb at a
     * time, so avoid that issue here: */
    if (sizeof(off_t) == 8 && *len > INT_MAX) {
        *len = INT_MAX;
    }
#endif

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

    if (sock->options & APR_INCOMPLETE_WRITE) {
        sock->options &= ~APR_INCOMPLETE_WRITE;
        goto do_select;
    }

    do {
        rv = sendfile(sock->socketdes,    /* socket */
                      file->filedes, /* open file descriptor of the file to be sent */
                      &off,    /* where in the file to start */
                      *len);   /* number of bytes to send */
    } while (rv == -1 && errno == EINTR);

    while ((rv == -1) && (errno == EAGAIN || errno == EWOULDBLOCK) 
                      && (sock->timeout > 0)) {
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

            if (sock->timeout > 0) {
                sock->options |= APR_INCOMPLETE_WRITE;
            }
            return arv;
        }
        else {
            /* If the file got smaller mid-request, eventually the offset
             * becomes equal to the new file size and the kernel returns 0.  
             * Make this an error so the caller knows to log something and
             * exit.
             */
            return APR_