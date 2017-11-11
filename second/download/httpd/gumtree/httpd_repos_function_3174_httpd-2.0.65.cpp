apr_status_t apr_socket_sendfile(apr_socket_t * sock, apr_file_t * file,
                                 apr_hdtr_t * hdtr, apr_off_t * offset,
                                 apr_size_t * len, apr_int32_t flags)
{
    int i, ptr, rv = 0;
    void * hbuf=NULL, * tbuf=NULL;
    apr_status_t arv;
    struct sf_parms parms;

    if (!hdtr) {
        hdtr = &no_hdtr;
    }

    /* Ignore flags for now. */
    flags = 0;

    /* word to the wise: by default, AIX stores files sent by send_file()
     * in the network buffer cache...  there are supposedly scenarios
     * where the most recent copy of the file won't be sent, but I can't
     * recreate the potential problem, perhaps because of the way we
     * use send_file()...  if you suspect such a problem, try turning
     * on the SF_SYNC_CACHE flag
     */

    /* AIX can also send the headers/footers as part of the system call */
    parms.header_length = 0;
    if (hdtr && hdtr->numheaders) {
        if (hdtr->numheaders == 1) {
            parms.header_data = hdtr->headers[0].iov_base;
            parms.header_length = hdtr->headers[0].iov_len;
        }
        else {
            for (i = 0; i < hdtr->numheaders; i++) {
                parms.header_length += hdtr->headers[i].iov_len;
            }
#if 0
            /* Keepalives make apr_palloc a bad idea */
            hbuf = malloc(parms.header_length);
#else
            /* but headers are small, so maybe we can hold on to the
             * memory for the life of the socket...
             */
            hbuf = apr_palloc(sock->cntxt, parms.header_length);
#endif
            ptr = 0;
            for (i = 0; i < hdtr->numheaders; i++) {
                memcpy((char *)hbuf + ptr, hdtr->headers[i].iov_base,
                       hdtr->headers[i].iov_len);
                ptr += hdtr->headers[i].iov_len;
            }
            parms.header_data = hbuf;
        }
    }
    else parms.header_data = NULL;
    parms.trailer_length = 0;
    if (hdtr && hdtr->numtrailers) {
        if (hdtr->numtrailers == 1) {
            parms.trailer_data = hdtr->trailers[0].iov_base;
            parms.trailer_length = hdtr->trailers[0].iov_len;
        }
        else {
            for (i = 0; i < hdtr->numtrailers; i++) {
                parms.trailer_length += hdtr->trailers[i].iov_len;
            }
#if 0
            /* Keepalives make apr_palloc a bad idea */
            tbuf = malloc(parms.trailer_length);
#else
            tbuf = apr_palloc(sock->cntxt, parms.trailer_length);
#endif
            ptr = 0;
            for (i = 0; i < hdtr->numtrailers; i++) {
                memcpy((char *)tbuf + ptr, hdtr->trailers[i].iov_base,
                       hdtr->trailers[i].iov_len);
                ptr += hdtr->trailers[i].iov_len;
            }
            parms.trailer_data = tbuf;
        }
    }
    else {
        parms.trailer_data = NULL;
    }

    /* Whew! Headers and trailers set up. Now for the file data */

    parms.file_descriptor = file->filedes;
    parms.file_offset = *offset;
    parms.file_bytes = *len;

    /* O.K. All set up now. Let's go to town */

    if (sock->netmask & APR_INCOMPLETE_WRITE) {
        sock->netmask &= ~APR_INCOMPLETE_WRITE;
        goto do_select;
    }

    do {
        rv = send_file(&(sock->socketdes), /* socket */
                       &(parms),           /* all data */
                       flags);             /* flags */
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
                rv = send_file(&(sock->socketdes), /* socket */
                               &(parms),           /* all data */
                               flags);             /* flags */
            } while (rv == -1 && errno == EINTR);
        }
    }

    (*len) = parms.bytes_sent;

#if 0
    /* Clean up after ourselves */
    if(hbuf) free(hbuf);
    if(tbuf) free(tbuf);
#endif

    if (rv == -1) {
        return errno;
    }

    if (apr_is_option_set(sock->netmask, APR_SO_TIMEOUT) &&
        (parms.bytes_sent < (parms.file_bytes + parms.header_length + parms.trailer_length))) {
        sock->netmask |= APR_INCOMPLETE_WRITE;
    }

    return APR_SUCCESS;
}