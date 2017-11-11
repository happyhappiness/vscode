static apr_status_t sendfile_it_all(core_net_rec *c,
                                    apr_file_t *fd,
                                    apr_hdtr_t *hdtr,
                                    apr_off_t   file_offset,
                                    apr_size_t  file_bytes_left,
                                    apr_size_t  total_bytes_left,
                                    apr_size_t  *bytes_sent,
                                    apr_int32_t flags)
{
    apr_status_t rv;
#ifdef AP_DEBUG
    apr_interval_time_t timeout = 0;
#endif

    AP_DEBUG_ASSERT((apr_socket_timeout_get(c->client_socket, &timeout)
                         == APR_SUCCESS)
                    && timeout > 0);  /* socket must be in timeout mode */

    /* Reset the bytes_sent field */
    *bytes_sent = 0;

    do {
        apr_size_t tmplen = file_bytes_left;

        rv = apr_socket_sendfile(c->client_socket, fd, hdtr, &file_offset, &tmplen,
                                 flags);
        *bytes_sent += tmplen;
        total_bytes_left -= tmplen;
        if (!total_bytes_left || rv != APR_SUCCESS) {
            return rv;        /* normal case & error exit */
        }

        AP_DEBUG_ASSERT(total_bytes_left > 0 && tmplen > 0);

        /* partial write, oooh noooo...
         * Skip over any header data which was written
         */
        while (tmplen && hdtr->numheaders) {
            if (tmplen >= hdtr->headers[0].iov_len) {
                tmplen -= hdtr->headers[0].iov_len;
                --hdtr->numheaders;
                ++hdtr->headers;
            }
            else {
                char *iov_base = (char *)hdtr->headers[0].iov_base;

                hdtr->headers[0].iov_len -= tmplen;
                iov_base += tmplen;
                hdtr->headers[0].iov_base = iov_base;
                tmplen = 0;
            }
        }

        /* Skip over any file data which was written */

        if (tmplen <= file_bytes_left) {
            file_offset += tmplen;
            file_bytes_left -= tmplen;
            continue;
        }

        tmplen -= file_bytes_left;
        file_bytes_left = 0;
        file_offset = 0;

        /* Skip over any trailer data which was written */

        while (tmplen && hdtr->numtrailers) {
            if (tmplen >= hdtr->trailers[0].iov_len) {
                tmplen -= hdtr->trailers[0].iov_len;
                --hdtr->numtrailers;
                ++hdtr->trailers;
            }
            else {
                char *iov_base = (char *)hdtr->trailers[0].iov_base;

                hdtr->trailers[0].iov_len -= tmplen;
                iov_base += tmplen;
                hdtr->trailers[0].iov_base = iov_base;
                tmplen = 0;
            }
        }
    } while (1);
}