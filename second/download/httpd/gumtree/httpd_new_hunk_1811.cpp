        /* Take what was originally there and place it back on ctx->b */
        APR_BRIGADE_CONCAT(ctx->b, ctx->tmpbb);
    }
    return APR_SUCCESS;
}

static void setaside_remaining_output(ap_filter_t *f,
                                      core_output_filter_ctx_t *ctx,
                                      apr_bucket_brigade *bb,
                                      conn_rec *c);

static apr_status_t send_brigade_nonblocking(apr_socket_t *s,
                                             apr_bucket_brigade *bb,
                                             apr_size_t *bytes_written,
                                             conn_rec *c);

static void remove_empty_buckets(apr_bucket_brigade *bb);

static apr_status_t send_brigade_blocking(apr_socket_t *s,
                                          apr_bucket_brigade *bb,
                                          apr_size_t *bytes_written,
                                          conn_rec *c);

static apr_status_t writev_nonblocking(apr_socket_t *s,
                                       struct iovec *vec, apr_size_t nvec,
                                       apr_bucket_brigade *bb,
                                       apr_size_t *cumulative_bytes_written,
                                       conn_rec *c);

#if APR_HAS_SENDFILE
static apr_status_t sendfile_nonblocking(apr_socket_t *s,
                                         apr_bucket *bucket,
                                         apr_size_t *cumulative_bytes_written,
                                         conn_rec *c);
#endif

#define THRESHOLD_MIN_WRITE 4096
#define THRESHOLD_MAX_BUFFER 65536

/* Optional function coming from mod_logio, used for logging of output
 * traffic
 */
extern APR_OPTIONAL_FN_TYPE(ap_logio_add_bytes_out) *ap__logio_add_bytes_out;

apr_status_t ap_core_output_filter(ap_filter_t *f, apr_bucket_brigade *new_bb)
{
    conn_rec *c = f->c;
    core_net_rec *net = f->ctx;
    core_output_filter_ctx_t *ctx = net->out_ctx;
    apr_bucket_brigade *bb = NULL;
    apr_bucket *bucket, *next;
    apr_size_t bytes_in_brigade, non_file_bytes_in_brigade;
    apr_status_t rv;

    /* Fail quickly if the connection has already been aborted. */
    if (c->aborted) {
        if (new_bb != NULL) {
            apr_brigade_cleanup(new_bb);
        }
        return APR_ECONNABORTED;
    }

    if (ctx == NULL) {
        ctx = apr_pcalloc(c->pool, sizeof(*ctx));
        net->out_ctx = (core_output_filter_ctx_t *)ctx;
        rv = apr_socket_opt_set(net->client_socket, APR_SO_NONBLOCK, 1);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        /*
         * Need to create tmp brigade with correct lifetime. Passing
         * NULL to apr_brigade_split_ex would result in a brigade
         * allocated from bb->pool which might be wrong.
         */
        ctx->tmp_flush_bb = apr_brigade_create(c->pool, c->bucket_alloc);
    }

    if (new_bb != NULL) {
        for (bucket = APR_BRIGADE_FIRST(new_bb); bucket != APR_BRIGADE_SENTINEL(new_bb); bucket = APR_BUCKET_NEXT(bucket)) {
            if (bucket->length > 0) {
                ctx->bytes_in += bucket->length;
            }
        }
        bb = new_bb;
    }

    if ((ctx->buffered_bb != NULL) &&
        !APR_BRIGADE_EMPTY(ctx->buffered_bb)) {
        if (new_bb != NULL) {
            APR_BRIGADE_PREPEND(bb, ctx->buffered_bb);
        }
        else {
            bb = ctx->buffered_bb;
        }
        c->data_in_output_filters = 0;
    }
    else if (new_bb == NULL) {
        return APR_SUCCESS;
    }

    /* Scan through the brigade and decide whether to attempt a write,
     * based on the following rules:
     *
     *  1) The new_bb is null: Do a nonblocking write of as much as
     *     possible: do a nonblocking write of as much data as possible,
     *     then save the rest in ctx->buffered_bb.  (If new_bb == NULL,
     *     it probably means that the MPM is doing asynchronous write
     *     completion and has just determined that this connection
     *     is writable.)
     *
     *  2) The brigade contains a flush bucket: Do a blocking write
     *     of everything up that point.
     *
     *  3) The request is in CONN_STATE_HANDLER state, and the brigade
     *     contains at least THRESHOLD_MAX_BUFFER bytes in non-file
     *     buckets: Do blocking writes until the amount of data in the
     *     buffer is less than THRESHOLD_MAX_BUFFER.  (The point of this
     *     rule is to provide flow control, in case a handler is
     *     streaming out lots of data faster than the data can be
     *     sent to the client.)
     *
     *  4) The brigade contains at least THRESHOLD_MIN_WRITE
     *     bytes: Do a nonblocking write of as much data as possible,
     *     then save the rest in ctx->buffered_bb.
     */

    if (new_bb == NULL) {
        rv = send_brigade_nonblocking(net->client_socket, bb,
                                      &(ctx->bytes_written), c);
        if (APR_STATUS_IS_EAGAIN(rv)) {
            rv = APR_SUCCESS;
        }
        else if (rv != APR_SUCCESS) {
            /* The client has aborted the connection */
            c->aborted = 1;
        }
        setaside_remaining_output(f, ctx, bb, c);
        return rv;
    }

    bytes_in_brigade = 0;
    non_file_bytes_in_brigade = 0;
    for (bucket = APR_BRIGADE_FIRST(bb); bucket != APR_BRIGADE_SENTINEL(bb);
         bucket = next) {
        next = APR_BUCKET_NEXT(bucket);
        if (APR_BUCKET_IS_FLUSH(bucket)) {
            ctx->tmp_flush_bb = apr_brigade_split_ex(bb, next, ctx->tmp_flush_bb);
            rv = send_brigade_blocking(net->client_socket, bb,
                                       &(ctx->bytes_written), c);
            if (rv != APR_SUCCESS) {
                /* The client has aborted the connection */
                c->aborted = 1;
                return rv;
            }
            APR_BRIGADE_CONCAT(bb, ctx->tmp_flush_bb);
            next = APR_BRIGADE_FIRST(bb);
            bytes_in_brigade = 0;
            non_file_bytes_in_brigade = 0;
        }
        else if (!APR_BUCKET_IS_METADATA(bucket)) {
            if (bucket->length < 0) {
                const char *data;
                apr_size_t length;
                /* XXX support nonblocking read here? */
                rv = apr_bucket_read(bucket, &data, &length, APR_BLOCK_READ);
                if (rv != APR_SUCCESS) {
                    return rv;
                }
                /* reading may have split the bucket, so recompute next: */
                next = APR_BUCKET_NEXT(bucket);
            }
            bytes_in_brigade += bucket->length;
            if (!APR_BUCKET_IS_FILE(bucket)) {
                non_file_bytes_in_brigade += bucket->length;
            }
        }
    }

    if (non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER) {
        /* ### Writing the entire brigade may be excessive; we really just
         * ### need to send enough data to be under THRESHOLD_MAX_BUFFER.
         */
        rv = send_brigade_blocking(net->client_socket, bb,
                                   &(ctx->bytes_written), c);
        if (rv != APR_SUCCESS) {
            /* The client has aborted the connection */
            c->aborted = 1;
            return rv;
        }
    }
    else if (bytes_in_brigade >= THRESHOLD_MIN_WRITE) {
        rv = send_brigade_nonblocking(net->client_socket, bb,
                                      &(ctx->bytes_written), c);
        if ((rv != APR_SUCCESS) && (!APR_STATUS_IS_EAGAIN(rv))) {
            /* The client has aborted the connection */
            c->aborted = 1;
            return rv;
        }
    }

    setaside_remaining_output(f, ctx, bb, c);
    return APR_SUCCESS;
}

static void setaside_remaining_output(ap_filter_t *f,
                                      core_output_filter_ctx_t *ctx,
                                      apr_bucket_brigade *bb,
                                      conn_rec *c)
{
    if (bb == NULL) {
        return;
    }
    remove_empty_buckets(bb);
    if (!APR_BRIGADE_EMPTY(bb)) {
        c->data_in_output_filters = 1;
        if (bb != ctx->buffered_bb) {
            /* XXX should this use a separate deferred write pool, like
             * the original ap_core_output_filter?
             */
            ap_save_brigade(f, &(ctx->buffered_bb), &bb, c->pool);
            apr_brigade_cleanup(bb);
        }
    }
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

static apr_status_t send_brigade_nonblocking(apr_socket_t *s,
                                             apr_bucket_brigade *bb,
                                             apr_size_t *bytes_written,
                                             conn_rec *c)
{
    apr_bucket *bucket, *next;
    apr_status_t rv;
    struct iovec vec[MAX_IOVEC_TO_WRITE];
    apr_size_t nvec = 0;

    remove_empty_buckets(bb);

    for (bucket = APR_BRIGADE_FIRST(bb);
         bucket != APR_BRIGADE_SENTINEL(bb);
         bucket = next) {
        int did_sendfile = 0;
        next = APR_BUCKET_NEXT(bucket);
#if APR_HAS_SENDFILE
        if (APR_BUCKET_IS_FILE(bucket)) {
            apr_bucket_file *file_bucket = (apr_bucket_file *)(bucket->data);
            apr_file_t *fd = file_bucket->fd;
            /* Use sendfile to send this file unless:
             *   - the platform doesn't support sendfile,
             *   - the file is too small for sendfile to be useful, or
             *   - sendfile is disabled in the httpd config via "EnableSendfile off"
             */

            if ((apr_file_flags_get(fd) & APR_SENDFILE_ENABLED) &&
                (bucket->length >= AP_MIN_SENDFILE_BYTES)) {
                did_sendfile = 1;
                if (nvec > 0) {
                    (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 1);
                    rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
                    nvec = 0;
                    if (rv != APR_SUCCESS) {
                        (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 0);
                        return rv;
                    }
                }
                rv = sendfile_nonblocking(s, bucket, bytes_written, c);
                if (nvec > 0) {
                    (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 0);
                }
                if (rv != APR_SUCCESS) {
                    return rv;
                }
                break;
            }
        }
#endif /* APR_HAS_SENDFILE */
        if (!did_sendfile && !APR_BUCKET_IS_METADATA(bucket)) {
            const char *data;
            apr_size_t length;
            rv = apr_bucket_read(bucket, &data, &length, APR_BLOCK_READ);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            /* reading may have split the bucket, so recompute next: */
            next = APR_BUCKET_NEXT(bucket);
            vec[nvec].iov_base = (char *)data;
            vec[nvec].iov_len = length;
            nvec++;
            if (nvec == MAX_IOVEC_TO_WRITE) {
                rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
                nvec = 0;
                if (rv != APR_SUCCESS) {
                    return rv;
                }
                break;
            }
        }
    }

    if (nvec > 0) {
        rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    remove_empty_buckets(bb);

    return APR_SUCCESS;
}

static void remove_empty_buckets(apr_bucket_brigade *bb)
{
    apr_bucket *bucket;
    while (((bucket = APR_BRIGADE_FIRST(bb)) != APR_BRIGADE_SENTINEL(bb)) &&
           (APR_BUCKET_IS_METADATA(bucket) || (bucket->length == 0))) {
        APR_BUCKET_REMOVE(bucket);
        apr_bucket_destroy(bucket);
    }
}

static apr_status_t send_brigade_blocking(apr_socket_t *s,
                                          apr_bucket_brigade *bb,
                                          apr_size_t *bytes_written,
                                          conn_rec *c)
{
    apr_status_t rv;

    rv = APR_SUCCESS;
    while (!APR_BRIGADE_EMPTY(bb)) {
        rv = send_brigade_nonblocking(s, bb, bytes_written, c);
        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_EAGAIN(rv)) {
                /* Wait until we can send more data */
                apr_int32_t nsds;
                apr_interval_time_t timeout;
                apr_pollfd_t pollset;

                pollset.p = c->pool;
                pollset.desc_type = APR_POLL_SOCKET;
                pollset.reqevents = APR_POLLOUT;
                pollset.desc.s = s;
                apr_socket_timeout_get(s, &timeout);
                rv = apr_poll(&pollset, 1, &nsds, timeout);
                if (rv != APR_SUCCESS) {
                    break;
                }
            }
            else {
                break;
            }
        }
    }
    return rv;
}

static apr_status_t writev_nonblocking(apr_socket_t *s,
                                       struct iovec *vec, apr_size_t nvec,
                                       apr_bucket_brigade *bb,
                                       apr_size_t *cumulative_bytes_written,
                                       conn_rec *c)
{
    apr_status_t rv = APR_SUCCESS, arv;
    apr_size_t bytes_written = 0, bytes_to_write = 0;
    apr_size_t i, offset;
    apr_interval_time_t old_timeout;

    arv = apr_socket_timeout_get(s, &old_timeout);
    if (arv != APR_SUCCESS) {
        return arv;
    }
    arv = apr_socket_timeout_set(s, 0);
    if (arv != APR_SUCCESS) {
        return arv;
    }

    for (i = 0; i < nvec; i++) {
        bytes_to_write += vec[i].iov_len;
    }
    offset = 0;
    while (bytes_written < bytes_to_write) {
        apr_size_t n = 0;
        rv = apr_socket_sendv(s, vec + offset, nvec - offset, &n);
        if (n > 0) {
            bytes_written += n;
            for (i = offset; i < nvec; ) {
                apr_bucket *bucket = APR_BRIGADE_FIRST(bb);
                if (APR_BUCKET_IS_METADATA(bucket)) {
                    APR_BUCKET_REMOVE(bucket);
                    apr_bucket_destroy(bucket);
                }
                else if (n >= vec[i].iov_len) {
                    APR_BUCKET_REMOVE(bucket);
                    apr_bucket_destroy(bucket);
                    offset++;
                    n -= vec[i++].iov_len;
                }
                else {
                    apr_bucket_split(bucket, n);
                    APR_BUCKET_REMOVE(bucket);
                    apr_bucket_destroy(bucket);
                    vec[i].iov_len -= n;
                    vec[i].iov_base = (char *) vec[i].iov_base + n;
                    break;
                }
            }
        }
        if (rv != APR_SUCCESS) {
            break;
        }
    }
    if ((ap__logio_add_bytes_out != NULL) && (bytes_written > 0)) {
        ap__logio_add_bytes_out(c, bytes_written);
    }
    *cumulative_bytes_written += bytes_written;

    arv = apr_socket_timeout_set(s, old_timeout);
    if ((arv != APR_SUCCESS) && (rv == APR_SUCCESS)) {
        return arv;
    }
    else {
        return rv;
    }
}

#if APR_HAS_SENDFILE

static apr_status_t sendfile_nonblocking(apr_socket_t *s,
                                         apr_bucket *bucket,
                                         apr_size_t *cumulative_bytes_written,
                                         conn_rec *c)
{
    apr_status_t rv = APR_SUCCESS;
    apr_bucket_file *file_bucket;
    apr_file_t *fd;
    apr_size_t file_length;
    apr_off_t file_offset;
    apr_size_t bytes_written = 0;

    if (!APR_BUCKET_IS_FILE(bucket)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, c->base_server,
                     "core_filter: sendfile_nonblocking: "
                     "this should never happen");
        return APR_EGENERAL;
    }
    file_bucket = (apr_bucket_file *)(bucket->data);
    fd = file_bucket->fd;
    file_length = bucket->length;
    file_offset = bucket->start;

    if (bytes_written < file_length) {
        apr_size_t n = file_length - bytes_written;
        apr_status_t arv;
        apr_interval_time_t old_timeout;

        arv = apr_socket_timeout_get(s, &old_timeout);
        if (arv != APR_SUCCESS) {
            return arv;
        }
        arv = apr_socket_timeout_set(s, 0);
        if (arv != APR_SUCCESS) {
            return arv;
        }
        rv = apr_socket_sendfile(s, fd, NULL, &file_offset, &n, 0);
        if (rv == APR_SUCCESS) {
            bytes_written += n;
            file_offset += n;
        }
        arv = apr_socket_timeout_set(s, old_timeout);
        if ((arv != APR_SUCCESS) && (rv == APR_SUCCESS)) {
            rv = arv;
        }
    }
    if ((ap__logio_add_bytes_out != NULL) && (bytes_written > 0)) {
        ap__logio_add_bytes_out(c, bytes_written);
    }
    *cumulative_bytes_written += bytes_written;
    if ((bytes_written < file_length) && (bytes_written > 0)) {
        apr_bucket_split(bucket, bytes_written);
        APR_BUCKET_REMOVE(bucket);
        apr_bucket_destroy(bucket);
    }
    else if (bytes_written == file_length) {
        APR_BUCKET_REMOVE(bucket);
        apr_bucket_destroy(bucket);
    }
    return rv;
}

#endif
