apr_status_t apr_socket_sendfile(apr_socket_t *sock, apr_file_t *file,
                                 apr_hdtr_t *hdtr, apr_off_t *offset,
                                 apr_size_t *len, apr_int32_t flags)
{
    int i;
    apr_ssize_t rc;
    apr_size_t nbytes = *len, headerlen, trailerlen;
    struct iovec hdtrarray[2];
    char *headerbuf, *trailerbuf;

#if APR_HAS_LARGE_FILES && defined(HAVE_SENDFILE64)
    /* later HP-UXes have a sendfile64() */
#define sendfile sendfile64
    apr_off_t off = *offset;

#elif APR_HAS_LARGE_FILES && SIZEOF_OFF_T == 4
    /* HP-UX 11.00 doesn't have a sendfile64(): fail if trying to send
     * past the 2Gb limit */
    off_t off;

    if ((apr_int64_t)*offset + *len > INT_MAX) {
        return EINVAL;
    }
    off = *offset;
#else
    apr_off_t off = *offset;
#endif

    if (!hdtr) {
        hdtr = &no_hdtr;
    }

    /* Ignore flags for now. */
    flags = 0;

    /* HP-UX can only send one header iovec and one footer iovec; try to
     * only allocate storage to combine input iovecs when we really have to
     */

    switch(hdtr->numheaders) {
    case 0:
        hdtrarray[0].iov_base = NULL;
        hdtrarray[0].iov_len = 0;
        break;
    case 1:
        hdtrarray[0] = hdtr->headers[0];
        break;
    default:
        headerlen = 0;
        for (i = 0; i < hdtr->numheaders; i++) {
            headerlen += hdtr->headers[i].iov_len;
        }  

        /* XXX:  BUHHH? wow, what a memory leak! */
        headerbuf = hdtrarray[0].iov_base = apr_palloc(sock->pool, headerlen);
        hdtrarray[0].iov_len = headerlen;

        for (i = 0; i < hdtr->numheaders; i++) {
            memcpy(headerbuf, hdtr->headers[i].iov_base,
                   hdtr->headers[i].iov_len);
            headerbuf += hdtr->headers[i].iov_len;
        }
    }

    switch(hdtr->numtrailers) {
    case 0:
        hdtrarray[1].iov_base = NULL;
        hdtrarray[1].iov_len = 0;
        break;
    case 1:
        hdtrarray[1] = hdtr->trailers[0];
        break;
    default:
        trailerlen = 0;
        for (i = 0; i < hdtr->numtrailers; i++) {
            trailerlen += hdtr->trailers[i].iov_len;
        }

        /* XXX:  BUHHH? wow, what a memory leak! */
        trailerbuf = hdtrarray[1].iov_base = apr_palloc(sock->pool, trailerlen);
        hdtrarray[1].iov_len = trailerlen;

        for (i = 0; i < hdtr->numtrailers; i++) {
            memcpy(trailerbuf, hdtr->trailers[i].iov_base,
                   hdtr->trailers[i].iov_len);
            trailerbuf += hdtr->trailers[i].iov_len;
        }
    }

    do {
        if (nbytes) {       /* any bytes to send from the file? */
            rc = sendfile(sock->socketdes,      /* socket  */
                          file->filedes,        /* file descriptor to send */
                          off,                  /* where in the file to start */
                          nbytes,               /* number of bytes to send from file */
                          hdtrarray,            /* Headers/footers */
                          flags);               /* undefined, set to 0 */
        }
        else {              /* we can't call sendfile() with no bytes to send from the file */
            rc = writev(sock->socketdes, hdtrarray, 2);
        }
    } while (rc == -1 && errno == EINTR);

    while ((rc == -1) && (errno == EAGAIN || errno == EWOULDBLOCK) 
                      && (sock->timeout > 0)) {
        apr_status_t arv = apr_wait_for_io_or_timeout(NULL, sock, 0);

        if (arv != APR_SUCCESS) {
            *len = 0;
            return arv;
        }
        else {
            do {
                if (nbytes) {
                    rc = sendfile(sock->socketdes,    /* socket  */
                                  file->filedes,      /* file descriptor to send */
                                  off,                /* where in the file to start */
                                  nbytes,             /* number of bytes to send from file */
                                  hdtrarray,          /* Headers/footers */
                                  flags);             /* undefined, set to 0 */
                }
                else {      /* we can't call sendfile() with no bytes to send from the file */
                    rc = writev(sock->socketdes, hdtrarray, 2);
                }
            } while (rc == -1 && errno == EINTR);
        }
    }

    if (rc == -1) {
        *len = 0;
        return errno;
    }

    /* Set len to the number of bytes written */
    *len = rc;
    return APR_SUCCESS;
}