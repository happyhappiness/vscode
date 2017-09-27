             (ctx->state == BODY_LENGTH && ctx->remaining > 0)) &&
             f->r->expecting_100 && f->r->proto_num >= HTTP_VERSION(1,1) &&
             !(f->r->eos_sent || f->r->bytes_sent)) {
             if (!ap_is_HTTP_SUCCESS(f->r->status)) {
                 ctx->state = BODY_NONE;
                 ctx->eos_sent = 1;
-            }
-            else {
+            } else {
                 char *tmp;
                 int len;
 
                 /* if we send an interim response, we're no longer
                  * in a state of expecting one.
                  */
                 f->r->expecting_100 = 0;
                 tmp = apr_pstrcat(f->r->pool, AP_SERVER_PROTOCOL, " ",
-                                  ap_get_status_line(100), CRLF CRLF, NULL);
+                                  ap_get_status_line(HTTP_CONTINUE), CRLF CRLF,
+                                  NULL);
                 len = strlen(tmp);
                 ap_xlate_proto_to_ascii(tmp, len);
                 apr_brigade_cleanup(bb);
                 e = apr_bucket_pool_create(tmp, len, f->r->pool,
                                            f->c->bucket_alloc);
                 APR_BRIGADE_INSERT_HEAD(bb, e);
                 e = apr_bucket_flush_create(f->c->bucket_alloc);
                 APR_BRIGADE_INSERT_TAIL(bb, e);
 
-                rv = ap_pass_brigade(f->c->output_filters, bb);
-                if (rv != APR_SUCCESS) {
-                    return AP_FILTER_ERROR;
-                }
+                ap_pass_brigade(f->c->output_filters, bb);
             }
         }
-    }
-
-    /* sanity check in case we're read twice */
-    if (ctx->eos_sent) {
-        e = apr_bucket_eos_create(f->c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(b, e);
-        return APR_SUCCESS;
-    }
 
-    do {
-        apr_brigade_cleanup(b);
-        again = 0; /* until further notice */
-
-        /* read and handle the brigade */
-        switch (ctx->state) {
-        case BODY_CHUNK:
-        case BODY_CHUNK_PART:
-        case BODY_CHUNK_EXT:
-        case BODY_CHUNK_CR:
-        case BODY_CHUNK_LF:
-        case BODY_CHUNK_END:
-        case BODY_CHUNK_END_LF: {
+        /* We can't read the chunk until after sending 100 if required. */
+        if (ctx->state == BODY_CHUNK) {
+            apr_brigade_cleanup(bb);
 
-            rv = ap_get_brigade(f->next, b, AP_MODE_GETLINE, block, 0);
+            rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE,
+                                block, 0);
 
             /* for timeout */
-            if (block == APR_NONBLOCK_READ
-                    && ((rv == APR_SUCCESS && APR_BRIGADE_EMPTY(b))
-                            || (APR_STATUS_IS_EAGAIN(rv)))) {
+            if (block == APR_NONBLOCK_READ &&
+                ( (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)) ||
+                  (APR_STATUS_IS_EAGAIN(rv)) )) {
+                ctx->state = BODY_CHUNK_PART;
                 return APR_EAGAIN;
             }
 
-            if (rv == APR_EOF) {
-                return APR_INCOMPLETE;
+            if (rv == APR_SUCCESS) {
+                rv = get_chunk_line(ctx, bb, f->r->server->limit_req_line);
+                if (APR_STATUS_IS_EAGAIN(rv)) {
+                    apr_brigade_cleanup(bb);
+                    ctx->state = BODY_CHUNK_PART;
+                    return rv;
+                }
+                if (rv == APR_SUCCESS) {
+                    ctx->remaining = get_chunk_size(ctx->chunk_ln);
+                    if (ctx->remaining == INVALID_CHAR) {
+                        rv = APR_EGENERAL;
+                        http_error = HTTP_SERVICE_UNAVAILABLE;
+                    }
+                }
             }
+            apr_brigade_cleanup(bb);
 
-            if (rv != APR_SUCCESS) {
-                return rv;
+            /* Detect chunksize error (such as overflow) */
+            if (rv != APR_SUCCESS || ctx->remaining < 0) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "Error reading first chunk %s ", 
+                              (ctx->remaining < 0) ? "(overflow)" : "");
+                ctx->remaining = 0; /* Reset it in case we have to
+                                     * come back here later */
+                if (APR_STATUS_IS_TIMEUP(rv)) { 
+                    http_error = HTTP_REQUEST_TIME_OUT;
+                }
+                return bail_out_on_error(ctx, f, http_error);
             }
 
-            e = APR_BRIGADE_FIRST(b);
-            while (e != APR_BRIGADE_SENTINEL(b)) {
-                const char *buffer;
-                apr_size_t len;
+            if (!ctx->remaining) {
+                /* Handle trailers by calling ap_get_mime_headers again! */
+                ctx->state = BODY_NONE;
+                ap_get_mime_headers(f->r);
+                e = apr_bucket_eos_create(f->c->bucket_alloc);
+                APR_BRIGADE_INSERT_TAIL(b, e);
+                ctx->eos_sent = 1;
+                return APR_SUCCESS;
+            }
+        }
+    }
+    else {
+        bb = ctx->bb;
+    }
 
-                if (!APR_BUCKET_IS_METADATA(e)) {
-                    int parsing = 0;
+    if (ctx->eos_sent) {
+        e = apr_bucket_eos_create(f->c->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(b, e);
+        return APR_SUCCESS;
+    }
 
-                    rv = apr_bucket_read(e, &buffer, &len, APR_BLOCK_READ);
+    if (!ctx->remaining) {
+        switch (ctx->state) {
+        case BODY_NONE:
+            break;
+        case BODY_LENGTH:
+            e = apr_bucket_eos_create(f->c->bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(b, e);
+            ctx->eos_sent = 1;
+            return APR_SUCCESS;
+        case BODY_CHUNK:
+        case BODY_CHUNK_PART:
+            {
+                apr_brigade_cleanup(bb);
 
-                    if (rv == APR_SUCCESS) {
-                        parsing = 1;
-                        rv = parse_chunk_size(ctx, buffer, len,
-                                f->r->server->limit_req_fieldsize, strict);
+                /* We need to read the CRLF after the chunk.  */
+                if (ctx->state == BODY_CHUNK) {
+                    rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE,
+                                        block, 0);
+                    if (block == APR_NONBLOCK_READ &&
+                        ( (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)) ||
+                          (APR_STATUS_IS_EAGAIN(rv)) )) {
+                        return APR_EAGAIN;
                     }
+                    /* If we get an error, then leave */
                     if (rv != APR_SUCCESS) {
-                        ap_log_rerror(APLOG_MARK, APLOG_INFO, rv, f->r,
-                                      "Error reading/parsing chunk %s ",
-                                      (APR_ENOSPC == rv) ? "(overflow)" : "");
-                        if (parsing) {
-                            if (rv != APR_ENOSPC) {
-                                http_error = HTTP_BAD_REQUEST;
-                            }
-                            return bail_out_on_error(ctx, f, http_error);
-                        }
                         return rv;
                     }
+                    /*
+                     * We really don't care whats on this line. If it is RFC
+                     * compliant it should be only \r\n. If there is more
+                     * before we just ignore it as long as we do not get over
+                     * the limit for request lines.
+                     */
+                    rv = get_remaining_chunk_line(ctx, bb,
+                                                  f->r->server->limit_req_line);
+                    apr_brigade_cleanup(bb);
+                    if (APR_STATUS_IS_EAGAIN(rv)) {
+                        return rv;
+                    }
+                } else {
+                    rv = APR_SUCCESS;
                 }
 
-                apr_bucket_delete(e);
-                e = APR_BRIGADE_FIRST(b);
-            }
-            again = 1; /* come around again */
-
-            if (ctx->state == BODY_CHUNK_TRAILER) {
-                /* Treat UNSET as DISABLE - trailers aren't merged by default */
-                return read_chunked_trailers(ctx, f, b,
-                            conf->merge_trailers == AP_MERGE_TRAILERS_ENABLE);
-            }
-
-            break;
-        }
-        case BODY_NONE:
-        case BODY_LENGTH:
-        case BODY_CHUNK_DATA: {
-
-            /* Ensure that the caller can not go over our boundary point. */
-            if (ctx->state != BODY_NONE && ctx->remaining < readbytes) {
-                readbytes = ctx->remaining;
-            }
-            if (readbytes > 0) {
-                apr_off_t totalread;
-
-                rv = ap_get_brigade(f->next, b, mode, block, readbytes);
-
-                /* for timeout */
-                if (block == APR_NONBLOCK_READ
-                        && ((rv == APR_SUCCESS && APR_BRIGADE_EMPTY(b))
-                                || (APR_STATUS_IS_EAGAIN(rv)))) {
-                    return APR_EAGAIN;
-                }
-
-                if (rv == APR_EOF && ctx->state != BODY_NONE
-                        && ctx->remaining > 0) {
-                    return APR_INCOMPLETE;
-                }
-
-                if (rv != APR_SUCCESS) {
-                    return rv;
-                }
-
-                /* How many bytes did we just read? */
-                apr_brigade_length(b, 0, &totalread);
-
-                /* If this happens, we have a bucket of unknown length.  Die because
-                 * it means our assumptions have changed. */
-                AP_DEBUG_ASSERT(totalread >= 0);
-
-                if (ctx->state != BODY_NONE) {
-                    ctx->remaining -= totalread;
-                    if (ctx->remaining > 0) {
-                        e = APR_BRIGADE_LAST(b);
-                        if (APR_BUCKET_IS_EOS(e)) {
-                            apr_bucket_delete(e);
-                            return APR_INCOMPLETE;
-                        }
+                if (rv == APR_SUCCESS) {
+                    /* Read the real chunk line. */
+                    rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE,
+                                        block, 0);
+                    /* Test timeout */
+                    if (block == APR_NONBLOCK_READ &&
+                        ( (rv == APR_SUCCESS && APR_BRIGADE_EMPTY(bb)) ||
+                          (APR_STATUS_IS_EAGAIN(rv)) )) {
+                        ctx->state = BODY_CHUNK_PART;
+                        return APR_EAGAIN;
                     }
-                    else if (ctx->state == BODY_CHUNK_DATA) {
-                        /* next chunk please */
-                        ctx->state = BODY_CHUNK_END;
-                        ctx->chunk_used = 0;
+                    ctx->state = BODY_CHUNK;
+                    if (rv == APR_SUCCESS) {
+                        rv = get_chunk_line(ctx, bb, f->r->server->limit_req_line);
+                        if (APR_STATUS_IS_EAGAIN(rv)) {
+                            ctx->state = BODY_CHUNK_PART;
+                            apr_brigade_cleanup(bb);
+                            return rv;
+                        }
+                        if (rv == APR_SUCCESS) {
+                            ctx->remaining = get_chunk_size(ctx->chunk_ln);
+                            if (ctx->remaining == INVALID_CHAR) {
+                                rv = APR_EGENERAL;
+                                http_error = HTTP_SERVICE_UNAVAILABLE;
+                            }
+                        }
                     }
+                    apr_brigade_cleanup(bb);
                 }
 
-                /* We have a limit in effect. */
-                if (ctx->limit) {
-                    /* FIXME: Note that we might get slightly confused on
-                     * chunked inputs as we'd need to compensate for the chunk
-                     * lengths which may not really count.  This seems to be up
-                     * for interpretation.
-                     */
-                    ctx->limit_used += totalread;
-                    if (ctx->limit < ctx->limit_used) {
-                        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r,
-                                      "Read content length of "
-                                      "%" APR_OFF_T_FMT " is larger than the "
-                                      "configured limit of %" APR_OFF_T_FMT,
-                                      ctx->limit_used, ctx->limit);
-                        return bail_out_on_error(ctx, f,
-                                                 HTTP_REQUEST_ENTITY_TOO_LARGE);
+                /* Detect chunksize error (such as overflow) */
+                if (rv != APR_SUCCESS || ctx->remaining < 0) {
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "Error reading chunk %s ", 
+                                  (ctx->remaining < 0) ? "(overflow)" : "");
+                    ctx->remaining = 0; /* Reset it in case we have to
+                                         * come back here later */
+                    if (APR_STATUS_IS_TIMEUP(rv)) { 
+                        http_error = HTTP_REQUEST_TIME_OUT;
                     }
+                    return bail_out_on_error(ctx, f, http_error);
                 }
-            }
 
-            /* If we have no more bytes remaining on a C-L request,
-             * save the caller a round trip to discover EOS.
-             */
-            if (ctx->state == BODY_LENGTH && ctx->remaining == 0) {
-                e = apr_bucket_eos_create(f->c->bucket_alloc);
-                APR_BRIGADE_INSERT_TAIL(b, e);
-                ctx->eos_sent = 1;
+                if (!ctx->remaining) {
+                    /* Handle trailers by calling ap_get_mime_headers again! */
+                    ctx->state = BODY_NONE;
+                    ap_get_mime_headers(f->r);
+                    e = apr_bucket_eos_create(f->c->bucket_alloc);
+                    APR_BRIGADE_INSERT_TAIL(b, e);
+                    ctx->eos_sent = 1;
+                    return APR_SUCCESS;
+                }
             }
-
             break;
         }
-        case BODY_CHUNK_TRAILER: {
-
-            rv = ap_get_brigade(f->next, b, mode, block, readbytes);
-
-            /* for timeout */
-            if (block == APR_NONBLOCK_READ
-                    && ((rv == APR_SUCCESS && APR_BRIGADE_EMPTY(b))
-                            || (APR_STATUS_IS_EAGAIN(rv)))) {
-                return APR_EAGAIN;
-            }
-
-            if (rv != APR_SUCCESS) {
-                return rv;
-            }
+    }
 
-            break;
+    /* Ensure that the caller can not go over our boundary point. */
+    if (ctx->state == BODY_LENGTH || ctx->state == BODY_CHUNK) {
+        if (ctx->remaining < readbytes) {
+            readbytes = ctx->remaining;
         }
-        default: {
-            /* Should not happen */
-            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r,
-                          "Unexpected body state (%i)", (int)ctx->state);
-            return APR_EGENERAL;
-        }
-        }
-
-    } while (again);
+        AP_DEBUG_ASSERT(readbytes > 0);
+    }
 
-    return APR_SUCCESS;
-}
+    rv = ap_get_brigade(f->next, b, mode, block, readbytes);
 
-struct check_header_ctx {
-    request_rec *r;
-    int strict;
-};
-
-/* check a single header, to be used with apr_table_do() */
-static int check_header(struct check_header_ctx *ctx,
-                        const char *name, const char **val)
-{
-    const char *pos, *end;
-    char *dst = NULL;
-
-    if (name[0] == '\0') {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r,
-                      "Empty response header name, aborting request");
-        return 0;
+    if (rv != APR_SUCCESS) {
+        return rv;
     }
 
-    if (ctx->strict) { 
-        end = ap_scan_http_token(name);
-    }
-    else {
-        end = ap_scan_vchar_obstext(name);
-    }
-    if (*end) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r,
-                      "Response header name '%s' contains invalid "
-                      "characters, aborting request",
-                      name);
-        return 0;
-    }
+    /* How many bytes did we just read? */
+    apr_brigade_length(b, 0, &totalread);
 
-    for (pos = *val; *pos; pos = end) {
-        end = ap_scan_http_field_content(pos);
-        if (*end) {
-            if (end[0] != CR || end[1] != LF || (end[2] != ' ' &&
-                                                 end[2] != '\t')) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r,
-                              "Response header '%s' value of '%s' contains "
-                              "invalid characters, aborting request",
-                              name, pos);
-                return 0;
-            }
-            if (!dst) {
-                *val = dst = apr_palloc(ctx->r->pool, strlen(*val) + 1);
-            }
-        }
-        if (dst) {
-            memcpy(dst, pos, end - pos);
-            dst += end - pos;
-            if (*end) {
-                /* skip folding and replace with a single space */
-                end += 3 + strspn(end + 3, "\t ");
-                *dst++ = ' ';
-            }
+    /* If this happens, we have a bucket of unknown length.  Die because
+     * it means our assumptions have changed. */
+    AP_DEBUG_ASSERT(totalread >= 0);
+
+    if (ctx->state != BODY_NONE) {
+        ctx->remaining -= totalread;
+        if (ctx->remaining > 0) {
+            e = APR_BRIGADE_LAST(b);
+            if (APR_BUCKET_IS_EOS(e))
+                return APR_EOF;
         }
     }
-    if (dst) {
-        *dst = '\0';
+
+    /* If we have no more bytes remaining on a C-L request,
+     * save the callter a roundtrip to discover EOS.
+     */
+    if (ctx->state == BODY_LENGTH && ctx->remaining == 0) {
+        e = apr_bucket_eos_create(f->c->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(b, e);
     }
-    return 1;
-}
 
-static int check_headers_table(apr_table_t *t, struct check_header_ctx *ctx)
-{
-    const apr_array_header_t *headers = apr_table_elts(t);
-    apr_table_entry_t *header;
-    int i;
-
-    for (i = 0; i < headers->nelts; ++i) {
-        header = &((apr_table_entry_t *)headers->elts)[i];
-        if (!header->key) {
-            continue;
-        }
-        if (!check_header(ctx, header->key, (const char **)&header->val)) {
-            return 0;
+    /* We have a limit in effect. */
+    if (ctx->limit) {
+        /* FIXME: Note that we might get slightly confused on chunked inputs
+         * as we'd need to compensate for the chunk lengths which may not
+         * really count.  This seems to be up for interpretation.  */
+        ctx->limit_used += totalread;
+        if (ctx->limit < ctx->limit_used) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
+                          "Read content-length of %" APR_OFF_T_FMT
+                          " is larger than the configured limit"
+                          " of %" APR_OFF_T_FMT, ctx->limit_used, ctx->limit);
+            apr_brigade_cleanup(bb);
+            e = ap_bucket_error_create(HTTP_REQUEST_ENTITY_TOO_LARGE, NULL,
+                                       f->r->pool,
+                                       f->c->bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(bb, e);
+            e = apr_bucket_eos_create(f->c->bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(bb, e);
+            ctx->eos_sent = 1;
+            return ap_pass_brigade(f->r->output_filters, bb);
         }
     }
-    return 1;
+
+    return APR_SUCCESS;
 }
 
 /**
- * Check headers for HTTP conformance
- * @return 1 if ok, 0 if bad
+ * Parse a chunk extension, detect overflow.
+ * There are two error cases:
+ *  1) If the conversion would require too many bits, a -1 is returned.
+ *  2) If the conversion used the correct number of bits, but an overflow
+ *     caused only the sign bit to flip, then that negative number is
+ *     returned.
+ * In general, any negative number can be considered an overflow error.
  */
-static APR_INLINE int check_headers(request_rec *r)
+static long get_chunk_size(char *b)
 {
-    struct check_header_ctx ctx;
-    core_server_config *conf =
-        (core_server_config *)ap_get_module_config(r->server->module_config,
-                                                   &core_module);
+    long chunksize = 0;
+    size_t chunkbits = sizeof(long) * 8;
 
-    ctx.r = r;
-    ctx.strict = (conf->http_conformance != AP_HTTP_CONFORMANCE_UNSAFE);
-    return check_headers_table(r->headers_out, &ctx) &&
-           check_headers_table(r->err_headers_out, &ctx);
-}
+    ap_xlate_proto_from_ascii(b, strlen(b));
 
-static int check_headers_recursion(request_rec *r)
-{
-    void *check = NULL;
-    apr_pool_userdata_get(&check, "check_headers_recursion", r->pool);
-    if (check) {
-        return 1;
+    if (!apr_isxdigit(*b)) {
+        /*
+         * Detect invalid character at beginning. This also works for empty
+         * chunk size lines.
+         */
+        return INVALID_CHAR;
+    }
+    /* Skip leading zeros */
+    while (*b == '0') {
+        ++b;
     }
-    apr_pool_userdata_setn("true", "check_headers_recursion", NULL, r->pool);
-    return 0;
+
+    while (apr_isxdigit(*b) && (chunkbits > 0)) {
+        int xvalue = 0;
+
+        if (*b >= '0' && *b <= '9') {
+            xvalue = *b - '0';
+        }
+        else if (*b >= 'A' && *b <= 'F') {
+            xvalue = *b - 'A' + 0xa;
+        }
+        else if (*b >= 'a' && *b <= 'f') {
+            xvalue = *b - 'a' + 0xa;
+        }
+
+        chunksize = (chunksize << 4) | xvalue;
+        chunkbits -= 4;
+        ++b;
+    }
+    if (apr_isxdigit(*b) && (chunkbits <= 0)) {
+        /* overflow */
+        return -1;
+    }
+
+    return chunksize;
 }
 
 typedef struct header_struct {
     apr_pool_t *pool;
     apr_bucket_brigade *bb;
 } header_struct;
 
 /* Send a single HTTP header field to the client.  Note that this function
- * is used in calls to apr_table_do(), so don't change its interface.
+ * is used in calls to table_do(), so their interfaces are co-dependent.
+ * In other words, don't change this one without checking table_do in alloc.c.
  * It returns true unless there was a write error of some kind.
  */
 static int form_header_field(header_struct *h,
                              const char *fieldname, const char *fieldval)
 {
 #if APR_CHARSET_EBCDIC
