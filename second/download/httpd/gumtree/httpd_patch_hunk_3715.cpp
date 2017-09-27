                 e = apr_bucket_pool_create(tmp, len, f->r->pool,
                                            f->c->bucket_alloc);
                 APR_BRIGADE_INSERT_HEAD(bb, e);
                 e = apr_bucket_flush_create(f->c->bucket_alloc);
                 APR_BRIGADE_INSERT_TAIL(bb, e);
 
-                ap_pass_brigade(f->c->output_filters, bb);
+                rv = ap_pass_brigade(f->c->output_filters, bb);
+                if (rv != APR_SUCCESS) {
+                    return AP_FILTER_ERROR;
+                }
             }
         }
+    }
 
-        /* We can't read the chunk until after sending 100 if required. */
-        if (ctx->state == BODY_CHUNK) {
-            apr_brigade_cleanup(bb);
+    /* sanity check in case we're read twice */
+    if (ctx->eos_sent) {
+        e = apr_bucket_eos_create(f->c->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(b, e);
+        return APR_SUCCESS;
+    }
+
+    do {
+        apr_brigade_cleanup(b);
+        again = 0; /* until further notice */
+
+        /* read and handle the brigade */
+        switch (ctx->state) {
+        case BODY_CHUNK:
+        case BODY_CHUNK_PART:
+        case BODY_CHUNK_EXT:
+        case BODY_CHUNK_CR:
+        case BODY_CHUNK_LF:
+        case BODY_CHUNK_END:
+        case BODY_CHUNK_END_LF: {
 
-            rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE,
-                                block, 0);
+            rv = ap_get_brigade(f->next, b, AP_MODE_GETLINE, block, 0);
 
             /* for timeout */
-            if (block == APR_NONBLOCK_READ &&
-                ( (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)) ||
-                  (APR_STATUS_IS_EAGAIN(rv)) )) {
-                ctx->state = BODY_CHUNK_PART;
+            if (block == APR_NONBLOCK_READ
+                    && ((rv == APR_SUCCESS && APR_BRIGADE_EMPTY(b))
+                            || (APR_STATUS_IS_EAGAIN(rv)))) {
                 return APR_EAGAIN;
             }
 
-            if (rv == APR_SUCCESS) {
-                rv = get_chunk_line(ctx, bb, f->r->server->limit_req_line);
-                if (APR_STATUS_IS_EAGAIN(rv)) {
-                    apr_brigade_cleanup(bb);
-                    ctx->state = BODY_CHUNK_PART;
-                    return rv;
-                }
-                if (rv == APR_SUCCESS) {
-                    ctx->remaining = get_chunk_size(ctx->chunk_ln);
-                    if (ctx->remaining == INVALID_CHAR) {
-                        rv = APR_EGENERAL;
-                        http_error = HTTP_BAD_REQUEST;
-                    }
-                }
+            if (rv == APR_EOF) {
+                return APR_INCOMPLETE;
             }
-            apr_brigade_cleanup(bb);
 
-            /* Detect chunksize error (such as overflow) */
-            if (rv != APR_SUCCESS || ctx->remaining < 0) {
-                ap_log_rerror(APLOG_MARK, APLOG_INFO, rv, f->r, APLOGNO(01589) "Error reading first chunk %s ",
-                              (ctx->remaining < 0) ? "(overflow)" : "");
-                if (APR_STATUS_IS_TIMEUP(rv) || ctx->remaining > 0) {
-                    http_error = HTTP_REQUEST_TIME_OUT;
-                }
-                ctx->remaining = 0; /* Reset it in case we have to
-                                     * come back here later */
-                return bail_out_on_error(ctx, f, http_error);
+            if (rv != APR_SUCCESS) {
+                return rv;
             }
 
-            if (!ctx->remaining) {
-                return read_chunked_trailers(ctx, f, b,
-                        conf->merge_trailers == AP_MERGE_TRAILERS_ENABLE);
-            }
-        }
-    }
-    else {
-        bb = ctx->bb;
-    }
+            e = APR_BRIGADE_FIRST(b);
+            while (e != APR_BRIGADE_SENTINEL(b)) {
+                const char *buffer;
+                apr_size_t len;
 
-    if (ctx->eos_sent) {
-        e = apr_bucket_eos_create(f->c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(b, e);
-        return APR_SUCCESS;
-    }
+                if (!APR_BUCKET_IS_METADATA(e)) {
+                    int parsing = 0;
 
-    if (!ctx->remaining) {
-        switch (ctx->state) {
-        case BODY_NONE:
-            break;
-        case BODY_LENGTH:
-            e = apr_bucket_eos_create(f->c->bucket_alloc);
-            APR_BRIGADE_INSERT_TAIL(b, e);
-            ctx->eos_sent = 1;
-            return APR_SUCCESS;
-        case BODY_CHUNK:
-        case BODY_CHUNK_PART:
-            {
-                apr_brigade_cleanup(bb);
+                    rv = apr_bucket_read(e, &buffer, &len, APR_BLOCK_READ);
 
-                /* We need to read the CRLF after the chunk.  */
-                if (ctx->state == BODY_CHUNK) {
-                    rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE,
-                                        block, 0);
-                    if (block == APR_NONBLOCK_READ &&
-                        ( (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)) ||
-                          (APR_STATUS_IS_EAGAIN(rv)) )) {
-                        return APR_EAGAIN;
-                    }
-                    /* If we get an error, then leave */
-                    if (rv == APR_EOF) {
-                        return APR_INCOMPLETE;
+                    if (rv == APR_SUCCESS) {
+                        parsing = 1;
+                        rv = parse_chunk_size(ctx, buffer, len,
+                                f->r->server->limit_req_fieldsize);
                     }
                     if (rv != APR_SUCCESS) {
-                        return rv;
-                    }
-                    /*
-                     * We really don't care whats on this line. If it is RFC
-                     * compliant it should be only \r\n. If there is more
-                     * before we just ignore it as long as we do not get over
-                     * the limit for request lines.
-                     */
-                    rv = get_remaining_chunk_line(ctx, bb,
-                                                  f->r->server->limit_req_line);
-                    apr_brigade_cleanup(bb);
-                    if (APR_STATUS_IS_EAGAIN(rv)) {
-                        return rv;
-                    }
-                } else {
-                    rv = APR_SUCCESS;
-                }
-
-                if (rv == APR_SUCCESS) {
-                    /* Read the real chunk line. */
-                    rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE,
-                                        block, 0);
-                    /* Test timeout */
-                    if (block == APR_NONBLOCK_READ &&
-                        ( (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)) ||
-                          (APR_STATUS_IS_EAGAIN(rv)) )) {
-                        ctx->state = BODY_CHUNK_PART;
-                        return APR_EAGAIN;
-                    }
-                    ctx->state = BODY_CHUNK;
-                    if (rv == APR_SUCCESS) {
-                        rv = get_chunk_line(ctx, bb, f->r->server->limit_req_line);
-                        if (APR_STATUS_IS_EAGAIN(rv)) {
-                            ctx->state = BODY_CHUNK_PART;
-                            apr_brigade_cleanup(bb);
-                            return rv;
-                        }
-                        if (rv == APR_SUCCESS) {
-                            ctx->remaining = get_chunk_size(ctx->chunk_ln);
-                            if (ctx->remaining == INVALID_CHAR) {
-                                rv = APR_EGENERAL;
+                        ap_log_rerror(APLOG_MARK, APLOG_INFO, rv, f->r, APLOGNO(01590)
+                                      "Error reading/parsing chunk %s ",
+                                      (APR_ENOSPC == rv) ? "(overflow)" : "");
+                        if (parsing) {
+                            if (rv != APR_ENOSPC) {
                                 http_error = HTTP_BAD_REQUEST;
                             }
+                            return bail_out_on_error(ctx, f, http_error);
                         }
+                        return rv;
                     }
-                    apr_brigade_cleanup(bb);
                 }
 
-                /* Detect chunksize error (such as overflow) */
-                if (rv != APR_SUCCESS || ctx->remaining < 0) {
-                    ap_log_rerror(APLOG_MARK, APLOG_INFO, rv, f->r, APLOGNO(01590) "Error reading chunk %s ",
-                                  (ctx->remaining < 0) ? "(overflow)" : "");
-                    if (APR_STATUS_IS_TIMEUP(rv) || ctx->remaining > 0) {
-                        http_error = HTTP_REQUEST_TIME_OUT;
-                    }
-                    ctx->remaining = 0; /* Reset it in case we have to
-                                         * come back here later */
-                    return bail_out_on_error(ctx, f, http_error);
-                }
+                apr_bucket_delete(e);
+                e = APR_BRIGADE_FIRST(b);
+            }
+            again = 1; /* come around again */
 
-                if (!ctx->remaining) {
-                    return read_chunked_trailers(ctx, f, b,
+            if (ctx->state == BODY_CHUNK_TRAILER) {
+                /* Treat UNSET as DISABLE - trailers aren't merged by default */
+                return read_chunked_trailers(ctx, f, b,
                             conf->merge_trailers == AP_MERGE_TRAILERS_ENABLE);
-                }
             }
+
             break;
         }
-    }
+        case BODY_NONE:
+        case BODY_LENGTH:
+        case BODY_CHUNK_DATA: {
 
-    /* Ensure that the caller can not go over our boundary point. */
-    if (ctx->state == BODY_LENGTH || ctx->state == BODY_CHUNK) {
-        if (ctx->remaining < readbytes) {
-            readbytes = ctx->remaining;
-        }
-        AP_DEBUG_ASSERT(readbytes > 0);
-    }
+            /* Ensure that the caller can not go over our boundary point. */
+            if (ctx->state != BODY_NONE && ctx->remaining < readbytes) {
+                readbytes = ctx->remaining;
+            }
+            if (readbytes > 0) {
+                apr_off_t totalread;
+
+                rv = ap_get_brigade(f->next, b, mode, block, readbytes);
+
+                /* for timeout */
+                if (block == APR_NONBLOCK_READ
+                        && ((rv == APR_SUCCESS && APR_BRIGADE_EMPTY(b))
+                                || (APR_STATUS_IS_EAGAIN(rv)))) {
+                    return APR_EAGAIN;
+                }
 
-    rv = ap_get_brigade(f->next, b, mode, block, readbytes);
+                if (rv == APR_EOF && ctx->state != BODY_NONE
+                        && ctx->remaining > 0) {
+                    return APR_INCOMPLETE;
+                }
 
-    if (rv == APR_EOF && ctx->state != BODY_NONE &&
-            ctx->remaining > 0) {
-        return APR_INCOMPLETE;
-    }
-    if (rv != APR_SUCCESS) {
-        return rv;
-    }
+                if (rv != APR_SUCCESS) {
+                    return rv;
+                }
 
-    /* How many bytes did we just read? */
-    apr_brigade_length(b, 0, &totalread);
+                /* How many bytes did we just read? */
+                apr_brigade_length(b, 0, &totalread);
 
-    /* If this happens, we have a bucket of unknown length.  Die because
-     * it means our assumptions have changed. */
-    AP_DEBUG_ASSERT(totalread >= 0);
-
-    if (ctx->state != BODY_NONE) {
-        ctx->remaining -= totalread;
-        if (ctx->remaining > 0) {
-            e = APR_BRIGADE_LAST(b);
-            if (APR_BUCKET_IS_EOS(e)) {
-                apr_bucket_delete(e);
-                return APR_INCOMPLETE;
+                /* If this happens, we have a bucket of unknown length.  Die because
+                 * it means our assumptions have changed. */
+                AP_DEBUG_ASSERT(totalread >= 0);
+
+                if (ctx->state != BODY_NONE) {
+                    ctx->remaining -= totalread;
+                    if (ctx->remaining > 0) {
+                        e = APR_BRIGADE_LAST(b);
+                        if (APR_BUCKET_IS_EOS(e)) {
+                            apr_bucket_delete(e);
+                            return APR_INCOMPLETE;
+                        }
+                    }
+                    else if (ctx->state == BODY_CHUNK_DATA) {
+                        /* next chunk please */
+                        ctx->state = BODY_CHUNK_END;
+                        ctx->chunk_used = 0;
+                    }
+                }
+
+                /* We have a limit in effect. */
+                if (ctx->limit) {
+                    /* FIXME: Note that we might get slightly confused on
+                     * chunked inputs as we'd need to compensate for the chunk
+                     * lengths which may not really count.  This seems to be up
+                     * for interpretation.
+                     */
+                    ctx->limit_used += totalread;
+                    if (ctx->limit < ctx->limit_used) {
+                        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r,
+                                      APLOGNO(01591) "Read content length of "
+                                      "%" APR_OFF_T_FMT " is larger than the "
+                                      "configured limit of %" APR_OFF_T_FMT,
+                                      ctx->limit_used, ctx->limit);
+                        return bail_out_on_error(ctx, f,
+                                                 HTTP_REQUEST_ENTITY_TOO_LARGE);
+                    }
+                }
             }
-        }
-    }
 
-    /* If we have no more bytes remaining on a C-L request,
-     * save the callter a roundtrip to discover EOS.
-     */
-    if (ctx->state == BODY_LENGTH && ctx->remaining == 0) {
-        e = apr_bucket_eos_create(f->c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(b, e);
-    }
+            /* If we have no more bytes remaining on a C-L request,
+             * save the caller a round trip to discover EOS.
+             */
+            if (ctx->state == BODY_LENGTH && ctx->remaining == 0) {
+                e = apr_bucket_eos_create(f->c->bucket_alloc);
+                APR_BRIGADE_INSERT_TAIL(b, e);
+                ctx->eos_sent = 1;
+            }
 
-    /* We have a limit in effect. */
-    if (ctx->limit) {
-        /* FIXME: Note that we might get slightly confused on chunked inputs
-         * as we'd need to compensate for the chunk lengths which may not
-         * really count.  This seems to be up for interpretation.  */
-        ctx->limit_used += totalread;
-        if (ctx->limit < ctx->limit_used) {
-            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r, APLOGNO(01591)
-                          "Read content-length of %" APR_OFF_T_FMT
-                          " is larger than the configured limit"
-                          " of %" APR_OFF_T_FMT, ctx->limit_used, ctx->limit);
-            apr_brigade_cleanup(bb);
-            e = ap_bucket_error_create(HTTP_REQUEST_ENTITY_TOO_LARGE, NULL,
-                                       f->r->pool,
-                                       f->c->bucket_alloc);
-            APR_BRIGADE_INSERT_TAIL(bb, e);
-            e = apr_bucket_eos_create(f->c->bucket_alloc);
-            APR_BRIGADE_INSERT_TAIL(bb, e);
-            ctx->eos_sent = 1;
-            return ap_pass_brigade(f->r->output_filters, bb);
+            break;
         }
-    }
-
-    return APR_SUCCESS;
-}
-
-/**
- * Parse a chunk extension, detect overflow.
- * There are two error cases:
- *  1) If the conversion would require too many bits, a -1 is returned.
- *  2) If the conversion used the correct number of bits, but an overflow
- *     caused only the sign bit to flip, then that negative number is
- *     returned.
- * In general, any negative number can be considered an overflow error.
- */
-static long get_chunk_size(char *b)
-{
-    long chunksize = 0;
-    size_t chunkbits = sizeof(long) * 8;
+        case BODY_CHUNK_TRAILER: {
 
-    ap_xlate_proto_from_ascii(b, strlen(b));
+            rv = ap_get_brigade(f->next, b, mode, block, readbytes);
 
-    if (!apr_isxdigit(*b)) {
-        /*
-         * Detect invalid character at beginning. This also works for empty
-         * chunk size lines.
-         */
-        return INVALID_CHAR;
-    }
-    /* Skip leading zeros */
-    while (*b == '0') {
-        ++b;
-    }
+            /* for timeout */
+            if (block == APR_NONBLOCK_READ
+                    && ((rv == APR_SUCCESS && APR_BRIGADE_EMPTY(b))
+                            || (APR_STATUS_IS_EAGAIN(rv)))) {
+                return APR_EAGAIN;
+            }
 
-    while (apr_isxdigit(*b) && (chunkbits > 0)) {
-        int xvalue = 0;
+            if (rv != APR_SUCCESS) {
+                return rv;
+            }
 
-        if (*b >= '0' && *b <= '9') {
-            xvalue = *b - '0';
+            break;
         }
-        else if (*b >= 'A' && *b <= 'F') {
-            xvalue = *b - 'A' + 0xa;
+        default: {
+            /* Should not happen */
+            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r, APLOGNO(02901)
+                          "Unexpected body state (%i)", (int)ctx->state);
+            return APR_EGENERAL;
         }
-        else if (*b >= 'a' && *b <= 'f') {
-            xvalue = *b - 'a' + 0xa;
         }
 
-        chunksize = (chunksize << 4) | xvalue;
-        chunkbits -= 4;
-        ++b;
-    }
-    if (apr_isxdigit(*b)) {
-        /* overflow */
-        return -1;
-    }
+    } while (again);
 
-    return chunksize;
+    return APR_SUCCESS;
 }
 
 typedef struct header_struct {
     apr_pool_t *pool;
     apr_bucket_brigade *bb;
 } header_struct;
