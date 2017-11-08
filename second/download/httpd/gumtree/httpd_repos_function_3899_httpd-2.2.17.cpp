apr_status_t apr_socket_sendfile(apr_socket_t * sock, apr_file_t * file,
                                 apr_hdtr_t * hdtr, apr_off_t * offset,
                                 apr_size_t * len, apr_int32_t flags)
{
    off_t nbytes = 0;
    int rv;
#if defined(__FreeBSD_version) && __FreeBSD_version < 460001
    int i;
#endif
    struct sf_hdtr headerstruct;
    apr_size_t bytes_to_send = *len;

    /* Ignore flags for now. */
    flags = 0;

    if (!hdtr) {
        hdtr = &no_hdtr;
    }

#if defined(__FreeBSD_version) && __FreeBSD_version < 460001
    else if (hdtr->numheaders) {

        /* On early versions of FreeBSD sendfile, the number of bytes to send 
         * must include the length of the headers.  Don't look at the man page 
         * for this :(  Instead, look at the the logic in 
         * src/sys/kern/uipc_syscalls::sendfile().
         *
         * This was fixed in the middle of 4.6-STABLE
         */
        for (i = 0; i < hdtr->numheaders; i++) {
            bytes_to_send += hdtr->headers[i].iov_len;
        }
    }
#endif

    headerstruct.headers = hdtr->headers;
    headerstruct.hdr_cnt = hdtr->numheaders;
    headerstruct.trailers = hdtr->trailers;
    headerstruct.trl_cnt = hdtr->numtrailers;

    /* FreeBSD can send the headers/footers as part of the system call */
    do {
        if (sock->options & APR_INCOMPLETE_WRITE) {
            apr_status_t arv;
            sock->options &= ~APR_INCOMPLETE_WRITE;
            arv = apr_wait_for_io_or_timeout(NULL, sock, 0);
            if (arv != APR_SUCCESS) {
                *len = 0;
                return arv;
            }
        }
        if (bytes_to_send) {
            /* We won't dare call sendfile() if we don't have
             * header or file bytes to send because bytes_to_send == 0
             * means send the whole file.
             */
            rv = sendfile(file->filedes, /* file to be sent */
                          sock->socketdes, /* socket */
                          *offset,       /* where in the file to start */
                          bytes_to_send, /* number of bytes to send */
                          &headerstruct, /* Headers/footers */
                          &nbytes,       /* number of bytes written */
                          flags);        /* undefined, set to 0 */

            if (rv == -1) {
                if (errno == EAGAIN) {
                    if (sock->timeout > 0) {
                        sock->options |= APR_INCOMPLETE_WRITE;
                    }
                    /* FreeBSD's sendfile can return -1/EAGAIN even if it
                     * sent bytes.  Sanitize the result so we get normal EAGAIN
                     * semantics w.r.t. bytes sent.
                     */
                    if (nbytes) {
                        /* normal exit for a big file & non-blocking io */
                        (*len) = nbytes;
                        return APR_SUCCESS;
                    }
                }
            }
            else {       /* rv == 0 (or the kernel is broken) */
                if (nbytes == 0) {
                    /* Most likely the file got smaller after the stat.
                     * Return an error so the caller can do the Right Thing.
                     */
                    (*len) = nbytes;
                    return APR_EOF;
                }
            }
        }    
        else {
            /* just trailer bytes... use writev()
             */
            rv = writev(sock->socketdes,
                        hdtr->trailers,
                        hdtr->numtrailers);
            if (rv > 0) {
                nbytes = rv;
                rv = 0;
            }
            else {
                nbytes = 0;
            }
        }
        if ((rv == -1) && (errno == EAGAIN) 
                       && (sock->timeout > 0)) {
            apr_status_t arv = apr_wait_for_io_or_timeout(NULL, sock, 0);
            if (arv != APR_SUCCESS) {
                *len = 0;
                return arv;
            }
        }
    } while (rv == -1 && (errno == EINTR || errno 