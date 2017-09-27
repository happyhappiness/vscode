        conf->ct_output_filters = apr_hash_make(cmd->pool);
        old = NULL;
    }
    else {
        old = (ap_filter_rec_t*) apr_hash_get(conf->ct_output_filters, arg2,
                                              APR_HASH_KEY_STRING);
    }

    while (*arg &&
           (filter_name = ap_getword(cmd->pool, &arg, ';')) &&
           strcmp(filter_name, "")) {
        new = apr_pcalloc(cmd->pool, sizeof(ap_filter_rec_t));
        new->name = filter_name;

        /* We found something, so let's append it.  */
        if (old) {
            new->next = old;
        }
        old = new;
    }

    if (!new) {
        return "invalid filter name";
    }
    
    apr_hash_set(conf->ct_output_filters, arg2, APR_HASH_KEY_STRING, new);

    return NULL;
}
/* 
 * Insert filters requested by the AddOutputFilterByType 
 * configuration directive. We cannot add filters based 
 * on content-type until after the handler has started 
 * to run. Only then do we reliably know the content-type.
 */
void ap_add_output_filters_by_type(request_rec *r)
{
    core_dir_config *conf;
    const char *ctype, *ctypes;

    conf = (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                   &core_module);

    /* We can't do anything with proxy requests, no content-types or if
     * we don't have a filter configured.
     */
    if (r->proxyreq != PROXYREQ_NONE || !r->content_type ||
        !conf->ct_output_filters) {
        return;
    }

    ctypes = r->content_type;

    /* We must be able to handle decorated content-types.  */
    while (*ctypes && (ctype = ap_getword(r->pool, &ctypes, ';'))) {
        ap_filter_rec_t *ct_filter;
        ct_filter = apr_hash_get(conf->ct_output_filters, ctype,
                                 APR_HASH_KEY_STRING);
        while (ct_filter) {
            ap_add_output_filter(ct_filter->name, NULL, r, r->connection);
            ct_filter = ct_filter->next;
        }
    }

    return;
}

static apr_status_t writev_it_all(apr_socket_t *s,
                                  struct iovec *vec, int nvec,
                                  apr_size_t len, apr_size_t *nbytes)
{
    apr_size_t bytes_written = 0;
    apr_status_t rv;
    apr_size_t n = len;
    int i = 0;

    *nbytes = 0;

    /* XXX handle checking for non-blocking socket */
    while (bytes_written != len) {
        rv = apr_sendv(s, vec + i, nvec - i, &n);
        bytes_written += n;
        if (rv != APR_SUCCESS)
            return rv;

        *nbytes += n;

        /* If the write did not complete, adjust the iovecs and issue
         * apr_sendv again
         */
        if (bytes_written < len) {
            /* Skip over the vectors that have already been written */
            apr_size_t cnt = vec[i].iov_len;
            while (n >= cnt && i + 1 < nvec) {
                i++;
                cnt += vec[i].iov_len;
            }

            if (n < cnt) {
                /* Handle partial write of vec i */
                vec[i].iov_base = (char *) vec[i].iov_base +
                    (vec[i].iov_len - (cnt - n));
                vec[i].iov_len = cnt -n;
            }
        }

        n = len - bytes_written;
    }

    return APR_SUCCESS;
}

/* sendfile_it_all()
 *  send the entire file using sendfile()
 *  handle partial writes
 *  return only when all bytes have been sent or an error is encountered.
 */

#if APR_HAS_SENDFILE
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

        rv = apr_sendfile(c->client_socket, fd, hdtr, &file_offset, &tmplen,
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
#endif

/*
 * emulate_sendfile()
 * Sends the contents of file fd along with header/trailer bytes, if any,
 * to the network. emulate_sendfile will return only when all the bytes have been
 * sent (i.e., it handles partial writes) or on a network error condition.
 */
static apr_status_t emulate_sendfile(core_net_rec *c, apr_file_t *fd,
                                     apr_hdtr_t *hdtr, apr_off_t offset,
                                     apr_size_t length, apr_size_t *nbytes)
{
    apr_status_t rv = APR_SUCCESS;
    apr_int32_t togo;        /* Remaining number of bytes in the file to send */
    apr_size_t sendlen = 0;
    apr_size_t bytes_sent;
    apr_int32_t i;
    apr_off_t o;             /* Track the file offset for partial writes */
    char buffer[8192];

    *nbytes = 0;

    /* Send the headers
     * writev_it_all handles partial writes.
     * XXX: optimization... if headers are less than MIN_WRITE_SIZE, copy
     * them into buffer
     */
    if (hdtr && hdtr->numheaders > 0 ) {
        for (i = 0; i < hdtr->numheaders; i++) {
            sendlen += hdtr->headers[i].iov_len;
        }

        rv = writev_it_all(c->client_socket, hdtr->headers, hdtr->numheaders,
                           sendlen, &bytes_sent);
        if (rv == APR_SUCCESS)
            *nbytes += bytes_sent;     /* track total bytes sent */
    }

    /* Seek the file to 'offset' */
    if (offset >= 0 && rv == APR_SUCCESS) {
        rv = apr_file_seek(fd, APR_SET, &offset);
    }

    /* Send the file, making sure to handle partial writes */
    togo = length;
    while (rv == APR_SUCCESS && togo) {
        sendlen = togo > sizeof(buffer) ? sizeof(buffer) : togo;
        o = 0;
        rv = apr_file_read(fd, buffer, &sendlen);
        while (rv == APR_SUCCESS && sendlen) {
            bytes_sent = sendlen;
            rv = apr_send(c->client_socket, &buffer[o], &bytes_sent);
            if (rv == APR_SUCCESS) {
                sendlen -= bytes_sent; /* sendlen != bytes_sent ==> partial write */
                o += bytes_sent;       /* o is where we are in the buffer */
                *nbytes += bytes_sent;
                togo -= bytes_sent;    /* track how much of the file we've sent */
            }
        }
    }

    /* Send the trailers
     * XXX: optimization... if it will fit, send this on the last send in the
     * loop above
     */
    sendlen = 0;
    if ( rv == APR_SUCCESS && hdtr && hdtr->numtrailers > 0 ) {
        for (i = 0; i < hdtr->numtrailers; i++) {
            sendlen += hdtr->trailers[i].iov_len;
        }
        rv = writev_it_all(c->client_socket, hdtr->trailers, hdtr->numtrailers,
                           sendlen, &bytes_sent);
        if (rv == APR_SUCCESS)
            *nbytes += bytes_sent;
    }

    return rv;
}

static const char *set_trace_enable(cmd_parms *cmd, void *dummy,
                                    const char *arg1)
{
    core_server_config *conf = ap_get_module_config(cmd->server->module_config,
                                                    &core_module);
    
    if (strcasecmp(arg1, "on") == 0) {
        conf->trace_enable = AP_TRACE_ENABLE;
    }
    else if (strcasecmp(arg1, "off") == 0) {
        conf->trace_enable = AP_TRACE_DISABLE;
    }
