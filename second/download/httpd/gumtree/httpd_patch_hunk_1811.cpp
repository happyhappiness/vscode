         /* Take what was originally there and place it back on ctx->b */
         APR_BRIGADE_CONCAT(ctx->b, ctx->tmpbb);
     }
     return APR_SUCCESS;
 }
 
-static apr_status_t writev_it_all(apr_socket_t *s,
-                                  struct iovec *vec, int nvec,
-                                  apr_size_t len, apr_size_t *nbytes)
-{
-    apr_size_t bytes_written = 0;
-    apr_status_t rv;
-    apr_size_t n = len;
-    int i = 0;
-
-    *nbytes = 0;
+static void setaside_remaining_output(ap_filter_t *f,
+                                      core_output_filter_ctx_t *ctx,
+                                      apr_bucket_brigade *bb,
+                                      conn_rec *c);
+
+static apr_status_t send_brigade_nonblocking(apr_socket_t *s,
+                                             apr_bucket_brigade *bb,
+                                             apr_size_t *bytes_written,
+                                             conn_rec *c);
+
+static void remove_empty_buckets(apr_bucket_brigade *bb);
+
+static apr_status_t send_brigade_blocking(apr_socket_t *s,
+                                          apr_bucket_brigade *bb,
+                                          apr_size_t *bytes_written,
+                                          conn_rec *c);
+
+static apr_status_t writev_nonblocking(apr_socket_t *s,
+                                       struct iovec *vec, apr_size_t nvec,
+                                       apr_bucket_brigade *bb,
+                                       apr_size_t *cumulative_bytes_written,
+                                       conn_rec *c);
 
-    /* XXX handle checking for non-blocking socket */
-    while (bytes_written != len) {
-        rv = apr_socket_sendv(s, vec + i, nvec - i, &n);
-        *nbytes += n;
-        bytes_written += n;
-        if (rv != APR_SUCCESS)
-            return rv;
-
-        /* If the write did not complete, adjust the iovecs and issue
-         * apr_socket_sendv again
-         */
-        if (bytes_written < len) {
-            /* Skip over the vectors that have already been written */
-            apr_size_t cnt = vec[i].iov_len;
-            while (n >= cnt && i + 1 < nvec) {
-                i++;
-                cnt += vec[i].iov_len;
-            }
-
-            if (n < cnt) {
-                /* Handle partial write of vec i */
-                vec[i].iov_base = (char *) vec[i].iov_base +
-                    (vec[i].iov_len - (cnt - n));
-                vec[i].iov_len = cnt -n;
-            }
-        }
-
-        n = len - bytes_written;
-    }
+#if APR_HAS_SENDFILE
+static apr_status_t sendfile_nonblocking(apr_socket_t *s,
+                                         apr_bucket *bucket,
+                                         apr_size_t *cumulative_bytes_written,
+                                         conn_rec *c);
+#endif
 
-    return APR_SUCCESS;
-}
+#define THRESHOLD_MIN_WRITE 4096
+#define THRESHOLD_MAX_BUFFER 65536
 
-/* sendfile_it_all()
- *  send the entire file using sendfile()
- *  handle partial writes
- *  return only when all bytes have been sent or an error is encountered.
+/* Optional function coming from mod_logio, used for logging of output
+ * traffic
  */
+extern APR_OPTIONAL_FN_TYPE(ap_logio_add_bytes_out) *ap__logio_add_bytes_out;
 
-#if APR_HAS_SENDFILE
-static apr_status_t sendfile_it_all(core_net_rec *c,
-                                    apr_file_t *fd,
-                                    apr_hdtr_t *hdtr,
-                                    apr_off_t   file_offset,
-                                    apr_size_t  file_bytes_left,
-                                    apr_size_t  total_bytes_left,
-                                    apr_size_t  *bytes_sent,
-                                    apr_int32_t flags)
+apr_status_t ap_core_output_filter(ap_filter_t *f, apr_bucket_brigade *new_bb)
 {
+    conn_rec *c = f->c;
+    core_net_rec *net = f->ctx;
+    core_output_filter_ctx_t *ctx = net->out_ctx;
+    apr_bucket_brigade *bb = NULL;
+    apr_bucket *bucket, *next;
+    apr_size_t bytes_in_brigade, non_file_bytes_in_brigade;
     apr_status_t rv;
-#ifdef AP_DEBUG
-    apr_interval_time_t timeout = 0;
-#endif
-
-    AP_DEBUG_ASSERT((apr_socket_timeout_get(c->client_socket, &timeout)
-                         == APR_SUCCESS)
-                    && timeout > 0);  /* socket must be in timeout mode */
-
-    /* Reset the bytes_sent field */
-    *bytes_sent = 0;
 
-    do {
-        apr_size_t tmplen = file_bytes_left;
-
-        rv = apr_socket_sendfile(c->client_socket, fd, hdtr, &file_offset, &tmplen,
-                                 flags);
-        *bytes_sent += tmplen;
-        total_bytes_left -= tmplen;
-        if (!total_bytes_left || rv != APR_SUCCESS) {
-            return rv;        /* normal case & error exit */
+    /* Fail quickly if the connection has already been aborted. */
+    if (c->aborted) {
+        if (new_bb != NULL) {
+            apr_brigade_cleanup(new_bb);
         }
+        return APR_ECONNABORTED;
+    }
 
-        AP_DEBUG_ASSERT(total_bytes_left > 0 && tmplen > 0);
-
-        /* partial write, oooh noooo...
-         * Skip over any header data which was written
+    if (ctx == NULL) {
+        ctx = apr_pcalloc(c->pool, sizeof(*ctx));
+        net->out_ctx = (core_output_filter_ctx_t *)ctx;
+        rv = apr_socket_opt_set(net->client_socket, APR_SO_NONBLOCK, 1);
+        if (rv != APR_SUCCESS) {
+            return rv;
+        }
+        /*
+         * Need to create tmp brigade with correct lifetime. Passing
+         * NULL to apr_brigade_split_ex would result in a brigade
+         * allocated from bb->pool which might be wrong.
          */
-        while (tmplen && hdtr->numheaders) {
-            if (tmplen >= hdtr->headers[0].iov_len) {
-                tmplen -= hdtr->headers[0].iov_len;
-                --hdtr->numheaders;
-                ++hdtr->headers;
-            }
-            else {
-                char *iov_base = (char *)hdtr->headers[0].iov_base;
+        ctx->tmp_flush_bb = apr_brigade_create(c->pool, c->bucket_alloc);
+    }
 
-                hdtr->headers[0].iov_len -= tmplen;
-                iov_base += tmplen;
-                hdtr->headers[0].iov_base = iov_base;
-                tmplen = 0;
+    if (new_bb != NULL) {
+        for (bucket = APR_BRIGADE_FIRST(new_bb); bucket != APR_BRIGADE_SENTINEL(new_bb); bucket = APR_BUCKET_NEXT(bucket)) {
+            if (bucket->length > 0) {
+                ctx->bytes_in += bucket->length;
             }
         }
+        bb = new_bb;
+    }
 
-        /* Skip over any file data which was written */
-
-        if (tmplen <= file_bytes_left) {
-            file_offset += tmplen;
-            file_bytes_left -= tmplen;
-            continue;
+    if ((ctx->buffered_bb != NULL) &&
+        !APR_BRIGADE_EMPTY(ctx->buffered_bb)) {
+        if (new_bb != NULL) {
+            APR_BRIGADE_PREPEND(bb, ctx->buffered_bb);
+        }
+        else {
+            bb = ctx->buffered_bb;
         }
+        c->data_in_output_filters = 0;
+    }
+    else if (new_bb == NULL) {
+        return APR_SUCCESS;
+    }
 
-        tmplen -= file_bytes_left;
-        file_bytes_left = 0;
-        file_offset = 0;
+    /* Scan through the brigade and decide whether to attempt a write,
+     * based on the following rules:
+     *
+     *  1) The new_bb is null: Do a nonblocking write of as much as
+     *     possible: do a nonblocking write of as much data as possible,
+     *     then save the rest in ctx->buffered_bb.  (If new_bb == NULL,
+     *     it probably means that the MPM is doing asynchronous write
+     *     completion and has just determined that this connection
+     *     is writable.)
+     *
+     *  2) The brigade contains a flush bucket: Do a blocking write
+     *     of everything up that point.
+     *
+     *  3) The request is in CONN_STATE_HANDLER state, and the brigade
+     *     contains at least THRESHOLD_MAX_BUFFER bytes in non-file
+     *     buckets: Do blocking writes until the amount of data in the
+     *     buffer is less than THRESHOLD_MAX_BUFFER.  (The point of this
+     *     rule is to provide flow control, in case a handler is
+     *     streaming out lots of data faster than the data can be
+     *     sent to the client.)
+     *
+     *  4) The brigade contains at least THRESHOLD_MIN_WRITE
+     *     bytes: Do a nonblocking write of as much data as possible,
+     *     then save the rest in ctx->buffered_bb.
+     */
 
-        /* Skip over any trailer data which was written */
+    if (new_bb == NULL) {
+        rv = send_brigade_nonblocking(net->client_socket, bb,
+                                      &(ctx->bytes_written), c);
+        if (APR_STATUS_IS_EAGAIN(rv)) {
+            rv = APR_SUCCESS;
+        }
+        else if (rv != APR_SUCCESS) {
+            /* The client has aborted the connection */
+            c->aborted = 1;
+        }
+        setaside_remaining_output(f, ctx, bb, c);
+        return rv;
+    }
 
-        while (tmplen && hdtr->numtrailers) {
-            if (tmplen >= hdtr->trailers[0].iov_len) {
-                tmplen -= hdtr->trailers[0].iov_len;
-                --hdtr->numtrailers;
-                ++hdtr->trailers;
+    bytes_in_brigade = 0;
+    non_file_bytes_in_brigade = 0;
+    for (bucket = APR_BRIGADE_FIRST(bb); bucket != APR_BRIGADE_SENTINEL(bb);
+         bucket = next) {
+        next = APR_BUCKET_NEXT(bucket);
+        if (APR_BUCKET_IS_FLUSH(bucket)) {
+            ctx->tmp_flush_bb = apr_brigade_split_ex(bb, next, ctx->tmp_flush_bb);
+            rv = send_brigade_blocking(net->client_socket, bb,
+                                       &(ctx->bytes_written), c);
+            if (rv != APR_SUCCESS) {
+                /* The client has aborted the connection */
+                c->aborted = 1;
+                return rv;
             }
-            else {
-                char *iov_base = (char *)hdtr->trailers[0].iov_base;
-
-                hdtr->trailers[0].iov_len -= tmplen;
-                iov_base += tmplen;
-                hdtr->trailers[0].iov_base = iov_base;
-                tmplen = 0;
+            APR_BRIGADE_CONCAT(bb, ctx->tmp_flush_bb);
+            next = APR_BRIGADE_FIRST(bb);
+            bytes_in_brigade = 0;
+            non_file_bytes_in_brigade = 0;
+        }
+        else if (!APR_BUCKET_IS_METADATA(bucket)) {
+            if (bucket->length < 0) {
+                const char *data;
+                apr_size_t length;
+                /* XXX support nonblocking read here? */
+                rv = apr_bucket_read(bucket, &data, &length, APR_BLOCK_READ);
+                if (rv != APR_SUCCESS) {
+                    return rv;
+                }
+                /* reading may have split the bucket, so recompute next: */
+                next = APR_BUCKET_NEXT(bucket);
+            }
+            bytes_in_brigade += bucket->length;
+            if (!APR_BUCKET_IS_FILE(bucket)) {
+                non_file_bytes_in_brigade += bucket->length;
             }
         }
-    } while (1);
-}
-#endif
-
-/*
- * emulate_sendfile()
- * Sends the contents of file fd along with header/trailer bytes, if any,
- * to the network. emulate_sendfile will return only when all the bytes have been
- * sent (i.e., it handles partial writes) or on a network error condition.
- */
-static apr_status_t emulate_sendfile(core_net_rec *c, apr_file_t *fd,
-                                     apr_hdtr_t *hdtr, apr_off_t offset,
-                                     apr_size_t length, apr_size_t *nbytes)
-{
-    apr_status_t rv = APR_SUCCESS;
-    apr_size_t togo;        /* Remaining number of bytes in the file to send */
-    apr_size_t sendlen = 0;
-    apr_size_t bytes_sent;
-    apr_int32_t i;
-    apr_off_t o;             /* Track the file offset for partial writes */
-    char buffer[8192];
-
-    *nbytes = 0;
-
-    /* Send the headers
-     * writev_it_all handles partial writes.
-     * XXX: optimization... if headers are less than MIN_WRITE_SIZE, copy
-     * them into buffer
-     */
-    if (hdtr && hdtr->numheaders > 0 ) {
-        for (i = 0; i < hdtr->numheaders; i++) {
-            sendlen += hdtr->headers[i].iov_len;
-        }
-
-        rv = writev_it_all(c->client_socket, hdtr->headers, hdtr->numheaders,
-                           sendlen, &bytes_sent);
-        *nbytes += bytes_sent;     /* track total bytes sent */
     }
 
-    /* Seek the file to 'offset' */
-    if (offset >= 0 && rv == APR_SUCCESS) {
-        rv = apr_file_seek(fd, APR_SET, &offset);
+    if (non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER) {
+        /* ### Writing the entire brigade may be excessive; we really just
+         * ### need to send enough data to be under THRESHOLD_MAX_BUFFER.
+         */
+        rv = send_brigade_blocking(net->client_socket, bb,
+                                   &(ctx->bytes_written), c);
+        if (rv != APR_SUCCESS) {
+            /* The client has aborted the connection */
+            c->aborted = 1;
+            return rv;
+        }
     }
-
-    /* Send the file, making sure to handle partial writes */
-    togo = length;
-    while (rv == APR_SUCCESS && togo) {
-        sendlen = togo > sizeof(buffer) ? sizeof(buffer) : togo;
-        o = 0;
-        rv = apr_file_read(fd, buffer, &sendlen);
-        while (rv == APR_SUCCESS && sendlen) {
-            bytes_sent = sendlen;
-            rv = apr_socket_send(c->client_socket, &buffer[o], &bytes_sent);
-            *nbytes += bytes_sent;
-            if (rv == APR_SUCCESS) {
-                sendlen -= bytes_sent; /* sendlen != bytes_sent ==> partial write */
-                o += bytes_sent;       /* o is where we are in the buffer */
-                togo -= bytes_sent;    /* track how much of the file we've sent */
-            }
+    else if (bytes_in_brigade >= THRESHOLD_MIN_WRITE) {
+        rv = send_brigade_nonblocking(net->client_socket, bb,
+                                      &(ctx->bytes_written), c);
+        if ((rv != APR_SUCCESS) && (!APR_STATUS_IS_EAGAIN(rv))) {
+            /* The client has aborted the connection */
+            c->aborted = 1;
+            return rv;
         }
     }
 
-    /* Send the trailers
-     * XXX: optimization... if it will fit, send this on the last send in the
-     * loop above
-     */
-    sendlen = 0;
-    if ( rv == APR_SUCCESS && hdtr && hdtr->numtrailers > 0 ) {
-        for (i = 0; i < hdtr->numtrailers; i++) {
-            sendlen += hdtr->trailers[i].iov_len;
-        }
-        rv = writev_it_all(c->client_socket, hdtr->trailers, hdtr->numtrailers,
-                           sendlen, &bytes_sent);
-        *nbytes += bytes_sent;
-    }
+    setaside_remaining_output(f, ctx, bb, c);
+    return APR_SUCCESS;
+}
 
-    return rv;
+static void setaside_remaining_output(ap_filter_t *f,
+                                      core_output_filter_ctx_t *ctx,
+                                      apr_bucket_brigade *bb,
+                                      conn_rec *c)
+{
+    if (bb == NULL) {
+        return;
+    }
+    remove_empty_buckets(bb);
+    if (!APR_BRIGADE_EMPTY(bb)) {
+        c->data_in_output_filters = 1;
+        if (bb != ctx->buffered_bb) {
+            /* XXX should this use a separate deferred write pool, like
+             * the original ap_core_output_filter?
+             */
+            ap_save_brigade(f, &(ctx->buffered_bb), &bb, c->pool);
+            apr_brigade_cleanup(bb);
+        }
+    }
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
 
-/* Optional function coming from mod_logio, used for logging of output
- * traffic
- */
-extern APR_OPTIONAL_FN_TYPE(ap_logio_add_bytes_out) *logio_add_bytes_out;
-
-apr_status_t ap_core_output_filter(ap_filter_t *f, apr_bucket_brigade *b)
+static apr_status_t send_brigade_nonblocking(apr_socket_t *s,
+                                             apr_bucket_brigade *bb,
+                                             apr_size_t *bytes_written,
+                                             conn_rec *c)
 {
+    apr_bucket *bucket, *next;
     apr_status_t rv;
-    apr_bucket_brigade *more;
-    conn_rec *c = f->c;
-    core_net_rec *net = f->ctx;
-    core_output_filter_ctx_t *ctx = net->out_ctx;
-    apr_read_type_e eblock = APR_NONBLOCK_READ;
-    apr_pool_t *input_pool = b->p;
-
-    /* Fail quickly if the connection has already been aborted. */
-    if (c->aborted) {
-        apr_brigade_cleanup(b);
-        return APR_ECONNABORTED;
-    }
-
-    if (ctx == NULL) {
-        ctx = apr_pcalloc(c->pool, sizeof(*ctx));
-        net->out_ctx = ctx;
-    }
-
-    /* If we have a saved brigade, concatenate the new brigade to it */
-    if (ctx->b) {
-        APR_BRIGADE_CONCAT(ctx->b, b);
-        b = ctx->b;
-        ctx->b = NULL;
-    }
-
-    /* Perform multiple passes over the brigade, sending batches of output
-       to the connection. */
-    while (b && !APR_BRIGADE_EMPTY(b)) {
-        apr_size_t nbytes = 0;
-        apr_bucket *last_e = NULL; /* initialized for debugging */
-        apr_bucket *e;
+    struct iovec vec[MAX_IOVEC_TO_WRITE];
+    apr_size_t nvec = 0;
 
-        /* one group of iovecs per pass over the brigade */
-        apr_size_t nvec = 0;
-        apr_size_t nvec_trailers = 0;
-        struct iovec vec[MAX_IOVEC_TO_WRITE];
-        struct iovec vec_trailers[MAX_IOVEC_TO_WRITE];
-
-        /* one file per pass over the brigade */
-        apr_file_t *fd = NULL;
-        apr_size_t flen = 0;
-        apr_off_t foffset = 0;
+    remove_empty_buckets(bb);
 
-        /* keep track of buckets that we've concatenated
-         * to avoid small writes
-         */
-        apr_bucket *last_merged_bucket = NULL;
-
-        /* tail of brigade if we need another pass */
-        more = NULL;
-
-        /* Iterate over the brigade: collect iovecs and/or a file */
-        for (e = APR_BRIGADE_FIRST(b);
-             e != APR_BRIGADE_SENTINEL(b);
-             e = APR_BUCKET_NEXT(e))
-        {
-            /* keep track of the last bucket processed */
-            last_e = e;
-            if (APR_BUCKET_IS_EOS(e) || AP_BUCKET_IS_EOC(e)) {
-                break;
-            }
-            else if (APR_BUCKET_IS_FLUSH(e)) {
-                if (e != APR_BRIGADE_LAST(b)) {
-                    more = apr_brigade_split(b, APR_BUCKET_NEXT(e));
-                }
-                break;
-            }
-
-            /* It doesn't make any sense to use sendfile for a file bucket
-             * that represents 10 bytes.
+    for (bucket = APR_BRIGADE_FIRST(bb);
+         bucket != APR_BRIGADE_SENTINEL(bb);
+         bucket = next) {
+        int did_sendfile = 0;
+        next = APR_BUCKET_NEXT(bucket);
+#if APR_HAS_SENDFILE
+        if (APR_BUCKET_IS_FILE(bucket)) {
+            apr_bucket_file *file_bucket = (apr_bucket_file *)(bucket->data);
+            apr_file_t *fd = file_bucket->fd;
+            /* Use sendfile to send this file unless:
+             *   - the platform doesn't support sendfile,
+             *   - the file is too small for sendfile to be useful, or
+             *   - sendfile is disabled in the httpd config via "EnableSendfile off"
              */
-            else if (APR_BUCKET_IS_FILE(e)
-                     && (e->length >= AP_MIN_SENDFILE_BYTES)) {
-                apr_bucket_file *a = e->data;
-
-                /* We can't handle more than one file bucket at a time
-                 * so we split here and send the file we have already
-                 * found.
-                 */
-                if (fd) {
-                    more = apr_brigade_split(b, e);
-                    break;
-                }
-
-                fd = a->fd;
-                flen = e->length;
-                foffset = e->start;
-            }
-            else {
-                const char *str;
-                apr_size_t n;
 
-                rv = apr_bucket_read(e, &str, &n, eblock);
-                if (APR_STATUS_IS_EAGAIN(rv)) {
-                    /* send what we have so far since we shouldn't expect more
-                     * output for a while...  next time we read, block
-                     */
-                    more = apr_brigade_split(b, e);
-                    eblock = APR_BLOCK_READ;
-                    break;
-                }
-                eblock = APR_NONBLOCK_READ;
-                if (n) {
-                    if (!fd) {
-                        if (nvec == MAX_IOVEC_TO_WRITE) {
-                            /* woah! too many. buffer them up, for use later. */
-                            apr_bucket *temp, *next;
-                            apr_bucket_brigade *temp_brig;
-
-                            if (nbytes >= AP_MIN_BYTES_TO_WRITE) {
-                                /* We have enough data in the iovec
-                                 * to justify doing a writev
-                                 */
-                                more = apr_brigade_split(b, e);
-                                break;
-                            }
-
-                            /* Create a temporary brigade as a means
-                             * of concatenating a bunch of buckets together
-                             */
-                            temp_brig = apr_brigade_create(f->c->pool,
-                                                       f->c->bucket_alloc);
-                            if (last_merged_bucket) {
-                                /* If we've concatenated together small
-                                 * buckets already in a previous pass,
-                                 * the initial buckets in this brigade
-                                 * are heap buckets that may have extra
-                                 * space left in them (because they
-                                 * were created by apr_brigade_write()).
-                                 * We can take advantage of this by
-                                 * building the new temp brigade out of
-                                 * these buckets, so that the content
-                                 * in them doesn't have to be copied again.
-                                 */
-                                APR_BRIGADE_PREPEND(b, temp_brig);
-                                brigade_move(temp_brig, b, APR_BUCKET_NEXT(last_merged_bucket));
-                            }
-
-                            temp = APR_BRIGADE_FIRST(b);
-                            while (temp != e) {
-                                apr_bucket *d;
-                                rv = apr_bucket_read(temp, &str, &n, APR_BLOCK_READ);
-                                apr_brigade_write(temp_brig, NULL, NULL, str, n);
-                                d = temp;
-                                temp = APR_BUCKET_NEXT(temp);
-                                apr_bucket_delete(d);
-                            }
-
-                            nvec = 0;
-                            nbytes = 0;
-                            temp = APR_BRIGADE_FIRST(temp_brig);
-                            APR_BUCKET_REMOVE(temp);
-                            APR_BRIGADE_INSERT_HEAD(b, temp);
-                            apr_bucket_read(temp, &str, &n, APR_BLOCK_READ);
-                            vec[nvec].iov_base = (char*) str;
-                            vec[nvec].iov_len = n;
-                            nvec++;
-
-                            /* Just in case the temporary brigade has
-                             * multiple buckets, recover the rest of
-                             * them and put them in the brigade that
-                             * we're sending.
-                             */
-                            for (next = APR_BRIGADE_FIRST(temp_brig);
-                                 next != APR_BRIGADE_SENTINEL(temp_brig);
-                                 next = APR_BRIGADE_FIRST(temp_brig)) {
-                                APR_BUCKET_REMOVE(next);
-                                APR_BUCKET_INSERT_AFTER(temp, next);
-                                temp = next;
-                                apr_bucket_read(next, &str, &n,
-                                                APR_BLOCK_READ);
-                                vec[nvec].iov_base = (char*) str;
-                                vec[nvec].iov_len = n;
-                                nvec++;
-                            }
-
-                            apr_brigade_destroy(temp_brig);
-
-                            last_merged_bucket = temp;
-                            e = temp;
-                            last_e = e;
-                        }
-                        else {
-                            vec[nvec].iov_base = (char*) str;
-                            vec[nvec].iov_len = n;
-                            nvec++;
-                        }
-                    }
-                    else {
-                        /* The bucket is a trailer to a file bucket */
-
-                        if (nvec_trailers == MAX_IOVEC_TO_WRITE) {
-                            /* woah! too many. stop now. */
-                            more = apr_brigade_split(b, e);
-                            break;
-                        }
-
-                        vec_trailers[nvec_trailers].iov_base = (char*) str;
-                        vec_trailers[nvec_trailers].iov_len = n;
-                        nvec_trailers++;
+            if ((apr_file_flags_get(fd) & APR_SENDFILE_ENABLED) &&
+                (bucket->length >= AP_MIN_SENDFILE_BYTES)) {
+                did_sendfile = 1;
+                if (nvec > 0) {
+                    (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 1);
+                    rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
+                    nvec = 0;
+                    if (rv != APR_SUCCESS) {
+                        (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 0);
+                        return rv;
                     }
-
-                    nbytes += n;
                 }
+                rv = sendfile_nonblocking(s, bucket, bytes_written, c);
+                if (nvec > 0) {
+                    (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 0);
+                }
+                if (rv != APR_SUCCESS) {
+                    return rv;
+                }
+                break;
             }
         }
-
-
-        /* Completed iterating over the brigade, now determine if we want
-         * to buffer the brigade or send the brigade out on the network.
-         *
-         * Save if we haven't accumulated enough bytes to send, the connection
-         * is not about to be closed, and:
-         *
-         *   1) we didn't see a file, we don't have more passes over the
-         *      brigade to perform,  AND we didn't stop at a FLUSH bucket.
-         *      (IOW, we will save plain old bytes such as HTTP headers)
-         * or
-         *   2) we hit the EOS and have a keep-alive connection
-         *      (IOW, this response is a bit more complex, but we save it
-         *       with the hope of concatenating with another response)
-         */
-        if (nbytes + flen < AP_MIN_BYTES_TO_WRITE
-            && !AP_BUCKET_IS_EOC(last_e)
-            && ((!fd && !more && !APR_BUCKET_IS_FLUSH(last_e))
-                || (APR_BUCKET_IS_EOS(last_e)
-                    && c->keepalive == AP_CONN_KEEPALIVE))) {
-
-            /* NEVER save an EOS in here.  If we are saving a brigade with
-             * an EOS bucket, then we are doing keepalive connections, and
-             * we want to process to second request fully.
-             */
-            if (APR_BUCKET_IS_EOS(last_e)) {
-                apr_bucket *bucket;
-                int file_bucket_saved = 0;
-                apr_bucket_delete(last_e);
-                for (bucket = APR_BRIGADE_FIRST(b);
-                     bucket != APR_BRIGADE_SENTINEL(b);
-                     bucket = APR_BUCKET_NEXT(bucket)) {
-
-                    /* Do a read on each bucket to pull in the
-                     * data from pipe and socket buckets, so
-                     * that we don't leave their file descriptors
-                     * open indefinitely.  Do the same for file
-                     * buckets, with one exception: allow the
-                     * first file bucket in the brigade to remain
-                     * a file bucket, so that we don't end up
-                     * doing an mmap+memcpy every time a client
-                     * requests a <8KB file over a keepalive
-                     * connection.
-                     */
-                    if (APR_BUCKET_IS_FILE(bucket) && !file_bucket_saved) {
-                        file_bucket_saved = 1;
-                    }
-                    else {
-                        const char *buf;
-                        apr_size_t len = 0;
-                        rv = apr_bucket_read(bucket, &buf, &len,
-                                             APR_BLOCK_READ);
-                        if (rv != APR_SUCCESS) {
-                            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv,
-                                          c, "core_output_filter:"
-                                          " Error reading from bucket.");
-                            return HTTP_INTERNAL_SERVER_ERROR;
-                        }
-                    }
-                }
+#endif /* APR_HAS_SENDFILE */
+        if (!did_sendfile && !APR_BUCKET_IS_METADATA(bucket)) {
+            const char *data;
+            apr_size_t length;
+            rv = apr_bucket_read(bucket, &data, &length, APR_BLOCK_READ);
+            if (rv != APR_SUCCESS) {
+                return rv;
             }
-            if (!ctx->deferred_write_pool) {
-                apr_pool_create(&ctx->deferred_write_pool, c->pool);
-                apr_pool_tag(ctx->deferred_write_pool, "deferred_write");
+            /* reading may have split the bucket, so recompute next: */
+            next = APR_BUCKET_NEXT(bucket);
+            vec[nvec].iov_base = (char *)data;
+            vec[nvec].iov_len = length;
+            nvec++;
+            if (nvec == MAX_IOVEC_TO_WRITE) {
+                rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
+                nvec = 0;
+                if (rv != APR_SUCCESS) {
+                    return rv;
+                }
+                break;
             }
-            ap_save_brigade(f, &ctx->b, &b, ctx->deferred_write_pool);
-
-            return APR_SUCCESS;
         }
+    }
 
-        if (fd) {
-            apr_hdtr_t hdtr;
-            apr_size_t bytes_sent;
+    if (nvec > 0) {
+        rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
+        if (rv != APR_SUCCESS) {
+            return rv;
+        }
+    }
 
-#if APR_HAS_SENDFILE
-            apr_int32_t flags = 0;
-#endif
+    remove_empty_buckets(bb);
 
-            memset(&hdtr, '\0', sizeof(hdtr));
-            if (nvec) {
-                hdtr.numheaders = nvec;
-                hdtr.headers = vec;
-            }
+    return APR_SUCCESS;
+}
 
-            if (nvec_trailers) {
-                hdtr.numtrailers = nvec_trailers;
-                hdtr.trailers = vec_trailers;
-            }
+static void remove_empty_buckets(apr_bucket_brigade *bb)
+{
+    apr_bucket *bucket;
+    while (((bucket = APR_BRIGADE_FIRST(bb)) != APR_BRIGADE_SENTINEL(bb)) &&
+           (APR_BUCKET_IS_METADATA(bucket) || (bucket->length == 0))) {
+        APR_BUCKET_REMOVE(bucket);
+        apr_bucket_destroy(bucket);
+    }
+}
 
-#if APR_HAS_SENDFILE
-            if (apr_file_flags_get(fd) & APR_SENDFILE_ENABLED) {
+static apr_status_t send_brigade_blocking(apr_socket_t *s,
+                                          apr_bucket_brigade *bb,
+                                          apr_size_t *bytes_written,
+                                          conn_rec *c)
+{
+    apr_status_t rv;
 
-                if (c->keepalive == AP_CONN_CLOSE && APR_BUCKET_IS_EOS(last_e)) {
-                    /* Prepare the socket to be reused */
-                    flags |= APR_SENDFILE_DISCONNECT_SOCKET;
-                }
-
-                rv = sendfile_it_all(net,      /* the network information   */
-                                     fd,       /* the file to send          */
-                                     &hdtr,    /* header and trailer iovecs */
-                                     foffset,  /* offset in the file to begin
-                                                  sending from              */
-                                     flen,     /* length of file            */
-                                     nbytes + flen, /* total length including
-                                                       headers              */
-                                     &bytes_sent,   /* how many bytes were
-                                                       sent                 */
-                                     flags);   /* apr_sendfile flags        */
+    rv = APR_SUCCESS;
+    while (!APR_BRIGADE_EMPTY(bb)) {
+        rv = send_brigade_nonblocking(s, bb, bytes_written, c);
+        if (rv != APR_SUCCESS) {
+            if (APR_STATUS_IS_EAGAIN(rv)) {
+                /* Wait until we can send more data */
+                apr_int32_t nsds;
+                apr_interval_time_t timeout;
+                apr_pollfd_t pollset;
+
+                pollset.p = c->pool;
+                pollset.desc_type = APR_POLL_SOCKET;
+                pollset.reqevents = APR_POLLOUT;
+                pollset.desc.s = s;
+                apr_socket_timeout_get(s, &timeout);
+                rv = apr_poll(&pollset, 1, &nsds, timeout);
+                if (rv != APR_SUCCESS) {
+                    break;
+                }
             }
-            else
-#endif
-            {
-                rv = emulate_sendfile(net, fd, &hdtr, foffset, flen,
-                                      &bytes_sent);
+            else {
+                break;
             }
-
-            if (logio_add_bytes_out && bytes_sent > 0)
-                logio_add_bytes_out(c, bytes_sent);
-
-            fd = NULL;
         }
-        else {
-            apr_size_t bytes_sent;
-
-            rv = writev_it_all(net->client_socket,
-                               vec, nvec,
-                               nbytes, &bytes_sent);
-
-            if (logio_add_bytes_out && bytes_sent > 0)
-                logio_add_bytes_out(c, bytes_sent);
-        }
-
-        apr_brigade_cleanup(b);
+    }
+    return rv;
+}
 
-        /* drive cleanups for resources which were set aside
-         * this may occur before or after termination of the request which
-         * created the resource
-         */
-        if (ctx->deferred_write_pool) {
-            if (more && more->p == ctx->deferred_write_pool) {
-                /* "more" belongs to the deferred_write_pool,
-                 * which is about to be cleared.
-                 */
-                if (APR_BRIGADE_EMPTY(more)) {
-                    more = NULL;
+static apr_status_t writev_nonblocking(apr_socket_t *s,
+                                       struct iovec *vec, apr_size_t nvec,
+                                       apr_bucket_brigade *bb,
+                                       apr_size_t *cumulative_bytes_written,
+                                       conn_rec *c)
+{
+    apr_status_t rv = APR_SUCCESS, arv;
+    apr_size_t bytes_written = 0, bytes_to_write = 0;
+    apr_size_t i, offset;
+    apr_interval_time_t old_timeout;
+
+    arv = apr_socket_timeout_get(s, &old_timeout);
+    if (arv != APR_SUCCESS) {
+        return arv;
+    }
+    arv = apr_socket_timeout_set(s, 0);
+    if (arv != APR_SUCCESS) {
+        return arv;
+    }
+
+    for (i = 0; i < nvec; i++) {
+        bytes_to_write += vec[i].iov_len;
+    }
+    offset = 0;
+    while (bytes_written < bytes_to_write) {
+        apr_size_t n = 0;
+        rv = apr_socket_sendv(s, vec + offset, nvec - offset, &n);
+        if (n > 0) {
+            bytes_written += n;
+            for (i = offset; i < nvec; ) {
+                apr_bucket *bucket = APR_BRIGADE_FIRST(bb);
+                if (APR_BUCKET_IS_METADATA(bucket)) {
+                    APR_BUCKET_REMOVE(bucket);
+                    apr_bucket_destroy(bucket);
+                }
+                else if (n >= vec[i].iov_len) {
+                    APR_BUCKET_REMOVE(bucket);
+                    apr_bucket_destroy(bucket);
+                    offset++;
+                    n -= vec[i++].iov_len;
                 }
                 else {
-                    /* uh oh... change more's lifetime
-                     * to the input brigade's lifetime
-                     */
-                    apr_bucket_brigade *tmp_more = more;
-                    more = NULL;
-                    ap_save_brigade(f, &more, &tmp_more, input_pool);
+                    apr_bucket_split(bucket, n);
+                    APR_BUCKET_REMOVE(bucket);
+                    apr_bucket_destroy(bucket);
+                    vec[i].iov_len -= n;
+                    vec[i].iov_base = (char *) vec[i].iov_base + n;
+                    break;
                 }
             }
-            apr_pool_clear(ctx->deferred_write_pool);
         }
-
         if (rv != APR_SUCCESS) {
-            ap_log_cerror(APLOG_MARK, APLOG_INFO, rv, c,
-                          "core_output_filter: writing data to the network");
-
-            if (more)
-                apr_brigade_cleanup(more);
+            break;
+        }
+    }
+    if ((ap__logio_add_bytes_out != NULL) && (bytes_written > 0)) {
+        ap__logio_add_bytes_out(c, bytes_written);
+    }
+    *cumulative_bytes_written += bytes_written;
 
-            /* No need to check for SUCCESS, we did that above. */
-            if (!APR_STATUS_IS_EAGAIN(rv)) {
-                c->aborted = 1;
-                return APR_ECONNABORTED;
-            }
+    arv = apr_socket_timeout_set(s, old_timeout);
+    if ((arv != APR_SUCCESS) && (rv == APR_SUCCESS)) {
+        return arv;
+    }
+    else {
+        return rv;
+    }
+}
 
-            return APR_SUCCESS;
-        }
+#if APR_HAS_SENDFILE
 
-        b = more;
-        more = NULL;
-    }  /* end while () */
+static apr_status_t sendfile_nonblocking(apr_socket_t *s,
+                                         apr_bucket *bucket,
+                                         apr_size_t *cumulative_bytes_written,
+                                         conn_rec *c)
+{
+    apr_status_t rv = APR_SUCCESS;
+    apr_bucket_file *file_bucket;
+    apr_file_t *fd;
+    apr_size_t file_length;
+    apr_off_t file_offset;
+    apr_size_t bytes_written = 0;
 
-    return APR_SUCCESS;
+    if (!APR_BUCKET_IS_FILE(bucket)) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, c->base_server,
+                     "core_filter: sendfile_nonblocking: "
+                     "this should never happen");
+        return APR_EGENERAL;
+    }
+    file_bucket = (apr_bucket_file *)(bucket->data);
+    fd = file_bucket->fd;
+    file_length = bucket->length;
+    file_offset = bucket->start;
+
+    if (bytes_written < file_length) {
+        apr_size_t n = file_length - bytes_written;
+        apr_status_t arv;
+        apr_interval_time_t old_timeout;
+
+        arv = apr_socket_timeout_get(s, &old_timeout);
+        if (arv != APR_SUCCESS) {
+            return arv;
+        }
+        arv = apr_socket_timeout_set(s, 0);
+        if (arv != APR_SUCCESS) {
+            return arv;
+        }
+        rv = apr_socket_sendfile(s, fd, NULL, &file_offset, &n, 0);
+        if (rv == APR_SUCCESS) {
+            bytes_written += n;
+            file_offset += n;
+        }
+        arv = apr_socket_timeout_set(s, old_timeout);
+        if ((arv != APR_SUCCESS) && (rv == APR_SUCCESS)) {
+            rv = arv;
+        }
+    }
+    if ((ap__logio_add_bytes_out != NULL) && (bytes_written > 0)) {
+        ap__logio_add_bytes_out(c, bytes_written);
+    }
+    *cumulative_bytes_written += bytes_written;
+    if ((bytes_written < file_length) && (bytes_written > 0)) {
+        apr_bucket_split(bucket, bytes_written);
+        APR_BUCKET_REMOVE(bucket);
+        apr_bucket_destroy(bucket);
+    }
+    else if (bytes_written == file_length) {
+        APR_BUCKET_REMOVE(bucket);
+        apr_bucket_destroy(bucket);
+    }
+    return rv;
 }
+
+#endif
