static apr_status_t core_output_filter(ap_filter_t *f, apr_bucket_brigade *b)
{
    apr_status_t rv;
    conn_rec *c = f->c;
    core_net_rec *net = f->ctx;
    core_output_filter_ctx_t *ctx = net->out_ctx;

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

        /* tail of brigade if we need another pass */
        apr_bucket_brigade *more = NULL;

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

        /* Iterate over the brigade: collect iovecs and/or a file */
        APR_BRIGADE_FOREACH(e, b) {
            /* keep track of the last bucket processed */
            last_e = e;
            if (APR_BUCKET_IS_EOS(e)) {
                break;
            }
            if (APR_BUCKET_IS_FLUSH(e)) {
                more = apr_brigade_split(b, APR_BUCKET_NEXT(e));
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

                rv = apr_bucket_read(e, &str, &n, APR_BLOCK_READ);
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
                                apr_bucket_brigade *bb;
                                bb = apr_brigade_split(b,
                                         APR_BUCKET_NEXT(last_merged_bucket));
                                temp_brig = b;
                                b = bb;
                            }
                            else {
                                temp_brig = apr_brigade_create(f->c->pool,
                                                           f->c->bucket_alloc);
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


        /* Completed iterating over the brigades, now determine if we want
         * to buffer the brigade or send the brigade out on the network.
         *
         * Save if:
         *
         *   1) we didn't see a file, we don't have more passes over the
         *      brigade to perform, we haven't accumulated enough bytes to
         *      send, AND we didn't stop at a FLUSH bucket.
         *      (IOW, we will save away plain old bytes)
         * or
         *   2) we hit the EOS and have a keep-alive connection
         *      (IOW, this response is a bit more complex, but we save it
         *       with the hope of concatenating with another response)
         */
        if ((!fd && !more
             && (nbytes + flen < AP_MIN_BYTES_TO_WRITE)
             && !APR_BUCKET_IS_FLUSH(last_e))
            || (nbytes + flen < AP_MIN_BYTES_TO_WRITE 
                && APR_BUCKET_IS_EOS(last_e)
                && c->keepalive == AP_CONN_KEEPALIVE)) {

            /* NEVER save an EOS in here.  If we are saving a brigade with
             * an EOS bucket, then we are doing keepalive connections, and
             * we want to process to second request fully.
             */
            if (APR_BUCKET_IS_EOS(last_e)) {
                apr_bucket *bucket = NULL;
                /* If we are in here, then this request is a keepalive.  We
                 * need to be certain that any data in a bucket is valid
                 * after the request_pool is cleared.
                 */
                if (ctx->b == NULL) {
                    ctx->b = apr_brigade_create(net->c->pool,
                                                net->c->bucket_alloc);
                }

                APR_BRIGADE_FOREACH(bucket, b) {
                    const char *str;
                    apr_size_t n;

                    rv = apr_bucket_read(bucket, &str, &n, APR_BLOCK_READ);

                    /* This apr_brigade_write does not use a flush function
                       because we assume that we will not write enough data
                       into it to cause a flush. However, if we *do* write
                       "too much", then we could end up with transient
                       buckets which would suck. This works for now, but is
                       a bit shaky if changes are made to some of the
                       buffering sizes. Let's do an assert to prevent
                       potential future problems... */
                    AP_DEBUG_ASSERT(AP_MIN_BYTES_TO_WRITE <=
                                    APR_BUCKET_BUFF_SIZE);
                    if (rv != APR_SUCCESS) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, c->base_server,
                                     "core_output_filter: Error reading from bucket.");
                        return HTTP_INTERNAL_SERVER_ERROR;
                    }

                    apr_brigade_write(ctx->b, NULL, NULL, str, n);
                }

                apr_brigade_destroy(b);
            }
            else {
                ap_save_brigade(f, &ctx->b, &b, c->pool);
            }

            return APR_SUCCESS;
        }

        if (fd) {
            apr_hdtr_t hdtr;
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
                                                   headers                */
                                 flags);   /* apr_sendfile flags        */

            /* If apr_sendfile() returns APR_ENOTIMPL, call emulate_sendfile().
             * emulate_sendfile() is useful to enable the same Apache binary
             * distribution to support Windows NT/2000 (supports TransmitFile)
             * and Win95/98 (do not support TransmitFile)
             */
            if (rv == APR_ENOTIMPL)
#endif
            {
                apr_size_t unused_bytes_sent;
                rv = emulate_sendfile(net, fd, &hdtr, foffset, flen,
                                      &unused_bytes_sent);
            }

            fd = NULL;
        }
        else {
            apr_size_t unused_bytes_sent;

            rv = writev_it_all(net->client_socket,
                               vec, nvec,
                               nbytes, &unused_bytes_sent);
        }

        apr_brigade_destroy(b);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
                         "core_output_filter: writing data to the network");

            if (more)
                apr_brigade_destroy(more);

            if (APR_STATUS_IS_ECONNABORTED(rv)
                || APR_STATUS_IS_ECONNRESET(rv)
                || APR_STATUS_IS_EPIPE(rv)) {
                c->aborted = 1;
            }

            /* The client has aborted, but the request was successful. We
             * will report success, and leave it to the access and error
             * logs to note that the connection was aborted.
             */
            return APR_SUCCESS;
        }

        b = more;
        more = NULL;
    }  /* end while () */

    return APR_SUCCESS;
}