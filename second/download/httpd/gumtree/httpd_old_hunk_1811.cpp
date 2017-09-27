        /* Take what was originally there and place it back on ctx->b */
        APR_BRIGADE_CONCAT(ctx->b, ctx->tmpbb);
    }
    return APR_SUCCESS;
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
        rv = apr_socket_sendv(s, vec + i, nvec - i, &n);
        *nbytes += n;
        bytes_written += n;
        if (rv != APR_SUCCESS)
            return rv;

        /* If the write did not complete, adjust the iovecs and issue
         * apr_socket_sendv again
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
    apr_size_t togo;        /* Remaining number of bytes in the file to send */
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
            rv = apr_socket_send(c->client_socket, &buffer[o], &bytes_sent);
            *nbytes += bytes_sent;
            if (rv == APR_SUCCESS) {
                sendlen -= bytes_sent; /* sendlen != bytes_sent ==> partial write */
                o += bytes_sent;       /* o is where we are in the buffer */
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
        *nbytes += bytes_sent;
    }

    return rv;
}

#ifndef APR_MAX_IOVEC_SIZE
#define MAX_IOVEC_TO_WRITE 16
#else
#if APR_MAX_IOVEC_SIZE > 16
#define MAX_IOVEC_TO_WRITE 16
#else
#define MAX_IOVEC_TO_WRITE APR_MAX_IOVEC_SIZE
#endif
#endif

/* Optional function coming from mod_logio, used for logging of output
 * traffic
 */
extern APR_OPTIONAL_FN_TYPE(ap_logio_add_bytes_out) *logio_add_bytes_out;

apr_status_t ap_core_output_filter(ap_filter_t *f, apr_bucket_brigade *b)
{
    apr_status_t rv;
    apr_bucket_brigade *more;
    conn_rec *c = f->c;
    core_net_rec *net = f->ctx;
    core_output_filter_ctx_t *ctx = net->out_ctx;
    apr_read_type_e eblock = APR_NONBLOCK_READ;
    apr_pool_t *input_pool = b->p;

    /* Fail quickly if the connection has already been aborted. */
    if (c->aborted) {
        apr_brigade_cleanup(b);
        return APR_ECONNABORTED;
    }

    if (ctx == NULL) {
        ctx = apr_pcalloc(c->pool, sizeof(*ctx));
        net->out_ctx = ctx;
    }

    /* If we have a saved brigade, concatenate the new brigade to it */
    if (ctx->b) {
        APR_BRIGADE_CONCAT(ctx->b, b);
        b = ctx->b;
        ctx->b = NULL;
    }

    /* Perform multiple passes over the brigade, sending batches of output
       to the connection. */
    while (b && !APR_BRIGADE_EMPTY(b)) {
        apr_size_t nbytes = 0;
        apr_bucket *last_e = NULL; /* initialized for debugging */
        apr_bucket *e;

        /* one group of iovecs per pass over the brigade */
        apr_size_t nvec = 0;
        apr_size_t nvec_trailers = 0;
        struct iovec vec[MAX_IOVEC_TO_WRITE];
        struct iovec vec_trailers[MAX_IOVEC_TO_WRITE];

        /* one file per pass over the brigade */
        apr_file_t *fd = NULL;
        apr_size_t flen = 0;
        apr_off_t foffset = 0;

        /* keep track of buckets that we've concatenated
         * to avoid small writes
         */
        apr_bucket *last_merged_bucket = NULL;

        /* tail of brigade if we need another pass */
        more = NULL;

        /* Iterate over the brigade: collect iovecs and/or a file */
        for (e = APR_BRIGADE_FIRST(b);
             e != APR_BRIGADE_SENTINEL(b);
             e = APR_BUCKET_NEXT(e))
        {
            /* keep track of the last bucket processed */
            last_e = e;
            if (APR_BUCKET_IS_EOS(e) || AP_BUCKET_IS_EOC(e)) {
                break;
            }
            else if (APR_BUCKET_IS_FLUSH(e)) {
                if (e != APR_BRIGADE_LAST(b)) {
                    more = apr_brigade_split(b, APR_BUCKET_NEXT(e));
                }
                break;
            }

            /* It doesn't make any sense to use sendfile for a file bucket
             * that represents 10 bytes.
             */
            else if (APR_BUCKET_IS_FILE(e)
                     && (e->length >= AP_MIN_SENDFILE_BYTES)) {
                apr_bucket_file *a = e->data;

                /* We can't handle more than one file bucket at a time
                 * so we split here and send the file we have already
                 * found.
                 */
                if (fd) {
                    more = apr_brigade_split(b, e);
                    break;
                }

                fd = a->fd;
                flen = e->length;
                foffset = e->start;
            }
            else {
                const char *str;
                apr_size_t n;

                rv = apr_bucket_read(e, &str, &n, eblock);
                if (APR_STATUS_IS_EAGAIN(rv)) {
                    /* send what we have so far since we shouldn't expect more
                     * output for a while...  next time we read, block
                     */
                    more = apr_brigade_split(b, e);
                    eblock = APR_BLOCK_READ;
                    break;
                }
                eblock = APR_NONBLOCK_READ;
                if (n) {
                    if (!fd) {
                        if (nvec == MAX_IOVEC_TO_WRITE) {
                            /* woah! too many. buffer them up, for use later. */
                            apr_bucket *temp, *next;
                            apr_bucket_brigade *temp_brig;

                            if (nbytes >= AP_MIN_BYTES_TO_WRITE) {
                                /* We have enough data in the iovec
                                 * to justify doing a writev
                                 */
                                more = apr_brigade_split(b, e);
                                break;
                            }

                            /* Create a temporary brigade as a means
                             * of concatenating a bunch of buckets together
                             */
                            temp_brig = apr_brigade_create(f->c->pool,
                                                       f->c->bucket_alloc);
                            if (last_merged_bucket) {
                                /* If we've concatenated together small
                                 * buckets already in a previous pass,
                                 * the initial buckets in this brigade
                                 * are heap buckets that may have extra
                                 * space left in them (because they
                                 * were created by apr_brigade_write()).
                                 * We can take advantage of this by
                                 * building the new temp brigade out of
                                 * these buckets, so that the content
                                 * in them doesn't have to be copied again.
                                 */
                                APR_BRIGADE_PREPEND(b, temp_brig);
                                brigade_move(temp_brig, b, APR_BUCKET_NEXT(last_merged_bucket));
                            }

                            temp = APR_BRIGADE_FIRST(b);
                            while (temp != e) {
                                apr_bucket *d;
                                rv = apr_bucket_read(temp, &str, &n, APR_BLOCK_READ);
                                apr_brigade_write(temp_brig, NULL, NULL, str, n);
                                d = temp;
                                temp = APR_BUCKET_NEXT(temp);
                                apr_bucket_delete(d);
                            }

                            nvec = 0;
                            nbytes = 0;
                            temp = APR_BRIGADE_FIRST(temp_brig);
                            APR_BUCKET_REMOVE(temp);
                            APR_BRIGADE_INSERT_HEAD(b, temp);
                            apr_bucket_read(temp, &str, &n, APR_BLOCK_READ);
                            vec[nvec].iov_base = (char*) str;
                            vec[nvec].iov_len = n;
                            nvec++;

                            /* Just in case the temporary brigade has
                             * multiple buckets, recover the rest of
                             * them and put them in the brigade that
                             * we're sending.
                             */
                            for (next = APR_BRIGADE_FIRST(temp_brig);
                                 next != APR_BRIGADE_SENTINEL(temp_brig);
                                 next = APR_BRIGADE_FIRST(temp_brig)) {
                                APR_BUCKET_REMOVE(next);
                                APR_BUCKET_INSERT_AFTER(temp, next);
                                temp = next;
                                apr_bucket_read(next, &str, &n,
                                                APR_BLOCK_READ);
                                vec[nvec].iov_base = (char*) str;
                                vec[nvec].iov_len = n;
                                nvec++;
                            }

                            apr_brigade_destroy(temp_brig);

                            last_merged_bucket = temp;
                            e = temp;
                            last_e = e;
                        }
                        else {
                            vec[nvec].iov_base = (char*) str;
                            vec[nvec].iov_len = n;
                            nvec++;
                        }
                    }
                    else {
                        /* The bucket is a trailer to a file bucket */

                        if (nvec_trailers == MAX_IOVEC_TO_WRITE) {
                            /* woah! too many. stop now. */
                            more = apr_brigade_split(b, e);
                            break;
                        }

                        vec_trailers[nvec_trailers].iov_base = (char*) str;
                        vec_trailers[nvec_trailers].iov_len = n;
                        nvec_trailers++;
                    }

                    nbytes += n;
                }
            }
        }


        /* Completed iterating over the brigade, now determine if we want
         * to buffer the brigade or send the brigade out on the network.
         *
         * Save if we haven't accumulated enough bytes to send, the connection
         * is not about to be closed, and:
         *
         *   1) we didn't see a file, we don't have more passes over the
         *      brigade to perform,  AND we didn't stop at a FLUSH bucket.
         *      (IOW, we will save plain old bytes such as HTTP headers)
         * or
         *   2) we hit the EOS and have a keep-alive connection
         *      (IOW, this response is a bit more complex, but we save it
         *       with the hope of concatenating with another response)
         */
        if (nbytes + flen < AP_MIN_BYTES_TO_WRITE
            && !AP_BUCKET_IS_EOC(last_e)
            && ((!fd && !more && !APR_BUCKET_IS_FLUSH(last_e))
                || (APR_BUCKET_IS_EOS(last_e)
                    && c->keepalive == AP_CONN_KEEPALIVE))) {

            /* NEVER save an EOS in here.  If we are saving a brigade with
             * an EOS bucket, then we are doing keepalive connections, and
             * we want to process to second request fully.
             */
            if (APR_BUCKET_IS_EOS(last_e)) {
                apr_bucket *bucket;
                int file_bucket_saved = 0;
                apr_bucket_delete(last_e);
                for (bucket = APR_BRIGADE_FIRST(b);
                     bucket != APR_BRIGADE_SENTINEL(b);
                     bucket = APR_BUCKET_NEXT(bucket)) {

                    /* Do a read on each bucket to pull in the
                     * data from pipe and socket buckets, so
                     * that we don't leave their file descriptors
                     * open indefinitely.  Do the same for file
                     * buckets, with one exception: allow the
                     * first file bucket in the brigade to remain
                     * a file bucket, so that we don't end up
                     * doing an mmap+memcpy every time a client
                     * requests a <8KB file over a keepalive
                     * connection.
                     */
                    if (APR_BUCKET_IS_FILE(bucket) && !file_bucket_saved) {
                        file_bucket_saved = 1;
                    }
                    else {
                        const char *buf;
                        apr_size_t len = 0;
                        rv = apr_bucket_read(bucket, &buf, &len,
                                             APR_BLOCK_READ);
                        if (rv != APR_SUCCESS) {
                            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv,
                                          c, "core_output_filter:"
                                          " Error reading from bucket.");
                            return HTTP_INTERNAL_SERVER_ERROR;
                        }
                    }
                }
            }
            if (!ctx->deferred_write_pool) {
                apr_pool_create(&ctx->deferred_write_pool, c->pool);
                apr_pool_tag(ctx->deferred_write_pool, "deferred_write");
            }
            ap_save_brigade(f, &ctx->b, &b, ctx->deferred_write_pool);

            return APR_SUCCESS;
        }

        if (fd) {
            apr_hdtr_t hdtr;
            apr_size_t bytes_sent;

#if APR_HAS_SENDFILE
            apr_int32_t flags = 0;
#endif

            memset(&hdtr, '\0', sizeof(hdtr));
            if (nvec) {
                hdtr.numheaders = nvec;
                hdtr.headers = vec;
            }

            if (nvec_trailers) {
                hdtr.numtrailers = nvec_trailers;
                hdtr.trailers = vec_trailers;
            }

#if APR_HAS_SENDFILE
            if (apr_file_flags_get(fd) & APR_SENDFILE_ENABLED) {

                if (c->keepalive == AP_CONN_CLOSE && APR_BUCKET_IS_EOS(last_e)) {
                    /* Prepare the socket to be reused */
                    flags |= APR_SENDFILE_DISCONNECT_SOCKET;
                }

                rv = sendfile_it_all(net,      /* the network information   */
                                     fd,       /* the file to send          */
                                     &hdtr,    /* header and trailer iovecs */
                                     foffset,  /* offset in the file to begin
                                                  sending from              */
                                     flen,     /* length of file            */
                                     nbytes + flen, /* total length including
                                                       headers              */
                                     &bytes_sent,   /* how many bytes were
                                                       sent                 */
                                     flags);   /* apr_sendfile flags        */
            }
            else
#endif
            {
                rv = emulate_sendfile(net, fd, &hdtr, foffset, flen,
                                      &bytes_sent);
            }

            if (logio_add_bytes_out && bytes_sent > 0)
                logio_add_bytes_out(c, bytes_sent);

            fd = NULL;
        }
        else {
            apr_size_t bytes_sent;

            rv = writev_it_all(net->client_socket,
                               vec, nvec,
                               nbytes, &bytes_sent);

            if (logio_add_bytes_out && bytes_sent > 0)
                logio_add_bytes_out(c, bytes_sent);
        }

        apr_brigade_cleanup(b);

        /* drive cleanups for resources which were set aside
         * this may occur before or after termination of the request which
         * created the resource
         */
        if (ctx->deferred_write_pool) {
            if (more && more->p == ctx->deferred_write_pool) {
                /* "more" belongs to the deferred_write_pool,
                 * which is about to be cleared.
                 */
                if (APR_BRIGADE_EMPTY(more)) {
                    more = NULL;
                }
                else {
                    /* uh oh... change more's lifetime
                     * to the input brigade's lifetime
                     */
                    apr_bucket_brigade *tmp_more = more;
                    more = NULL;
                    ap_save_brigade(f, &more, &tmp_more, input_pool);
                }
            }
            apr_pool_clear(ctx->deferred_write_pool);
        }

        if (rv != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, rv, c,
                          "core_output_filter: writing data to the network");

            if (more)
                apr_brigade_cleanup(more);

            /* No need to check for SUCCESS, we did that above. */
            if (!APR_STATUS_IS_EAGAIN(rv)) {
                c->aborted = 1;
                return APR_ECONNABORTED;
            }

            return APR_SUCCESS;
        }

        b = more;
        more = NULL;
    }  /* end while () */

    return APR_SUCCESS;
}
