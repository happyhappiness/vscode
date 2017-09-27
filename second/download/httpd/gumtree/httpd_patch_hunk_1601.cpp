 #include <stdarg.h>
 #endif
 #if APR_HAVE_UNISTD_H
 #include <unistd.h>
 #endif
 
-typedef struct http_filter_ctx
-{
+APLOG_USE_MODULE(http);
+
+#define INVALID_CHAR -2
+
+static long get_chunk_size(char *);
+
+typedef struct http_filter_ctx {
     apr_off_t remaining;
     apr_off_t limit;
     apr_off_t limit_used;
-    apr_int32_t chunk_used;
-    apr_int32_t chunk_bws;
-    apr_int32_t chunkbits;
-    enum
-    {
-        BODY_NONE, /* streamed data */
-        BODY_LENGTH, /* data constrained by content length */
-        BODY_CHUNK, /* chunk expected */
-        BODY_CHUNK_PART, /* chunk digits */
-        BODY_CHUNK_EXT, /* chunk extension */
-        BODY_CHUNK_CR, /* got space(s) after digits, expect [CR]LF or ext */
-        BODY_CHUNK_LF, /* got CR after digits or ext, expect LF */
-        BODY_CHUNK_DATA, /* data constrained by chunked encoding */
-        BODY_CHUNK_END, /* chunked data terminating CRLF */
-        BODY_CHUNK_END_LF, /* got CR after data, expect LF */
-        BODY_CHUNK_TRAILER /* trailers */
+    enum {
+        BODY_NONE,
+        BODY_LENGTH,
+        BODY_CHUNK,
+        BODY_CHUNK_PART
     } state;
-    unsigned int eos_sent :1;
+    int eos_sent;
+    char chunk_ln[32];
+    char *pos;
+    apr_off_t linesize;
     apr_bucket_brigade *bb;
 } http_ctx_t;
 
-/* bail out if some error in the HTTP input filter happens */
 static apr_status_t bail_out_on_error(http_ctx_t *ctx,
                                       ap_filter_t *f,
                                       int http_error)
 {
     apr_bucket *e;
     apr_bucket_brigade *bb = ctx->bb;
 
     apr_brigade_cleanup(bb);
-
-    if (f->r->proxyreq == PROXYREQ_RESPONSE) {
-        switch (http_error) {
-        case HTTP_REQUEST_ENTITY_TOO_LARGE:
-            return APR_ENOSPC;
-
-        case HTTP_REQUEST_TIME_OUT:
-            return APR_INCOMPLETE;
-
-        case HTTP_NOT_IMPLEMENTED:
-            return APR_ENOTIMPL;
-
-        default:
-            return APR_EGENERAL;
-        }
-    }
-
     e = ap_bucket_error_create(http_error,
                                NULL, f->r->pool,
                                f->c->bucket_alloc);
     APR_BRIGADE_INSERT_TAIL(bb, e);
     e = apr_bucket_eos_create(f->c->bucket_alloc);
     APR_BRIGADE_INSERT_TAIL(bb, e);
     ctx->eos_sent = 1;
-    /* If chunked encoding / content-length are corrupt, we may treat parts
-     * of this request's body as the next one's headers.
-     * To be safe, disable keep-alive.
-     */
-    f->r->connection->keepalive = AP_CONN_CLOSE;
     return ap_pass_brigade(f->r->output_filters, bb);
 }
 
-/**
- * Parse a chunk line with optional extension, detect overflow.
- * There are several error cases:
- *  1) If the chunk link is misformatted, APR_EINVAL is returned.
- *  2) If the conversion would require too many bits, APR_EGENERAL is returned.
- *  3) If the conversion used the correct number of bits, but an overflow
- *     caused only the sign bit to flip, then APR_ENOSPC is returned.
- * A negative chunk length always indicates an overflow error.
- */
-static apr_status_t parse_chunk_size(http_ctx_t *ctx, const char *buffer,
-                                     apr_size_t len, int linelimit, int strict)
+static apr_status_t get_remaining_chunk_line(http_ctx_t *ctx,
+                                             apr_bucket_brigade *b,
+                                             int linelimit)
 {
-    apr_size_t i = 0;
-
-    while (i < len) {
-        char c = buffer[i];
+    apr_status_t rv;
+    apr_off_t brigade_length;
+    apr_bucket *e;
+    const char *lineend;
+    apr_size_t len = 0;
 
-        ap_xlate_proto_from_ascii(&c, 1);
+    /*
+     * As the brigade b should have been requested in mode AP_MODE_GETLINE
+     * all buckets in this brigade are already some type of memory
+     * buckets (due to the needed scanning for LF in mode AP_MODE_GETLINE)
+     * or META buckets.
+     */
+    rv = apr_brigade_length(b, 0, &brigade_length);
+    if (rv != APR_SUCCESS) {
+        return rv;
+    }
+    /* Sanity check. Should never happen. See above. */
+    if (brigade_length == -1) {
+        return APR_EGENERAL;
+    }
+    if (!brigade_length) {
+        return APR_EAGAIN;
+    }
+    ctx->linesize += brigade_length;
+    if (ctx->linesize > linelimit) {
+        return APR_ENOSPC;
+    }
+    /*
+     * As all buckets are already some type of memory buckets or META buckets
+     * (see above), we only need to check the last byte in the last data bucket.
+     */
+    for (e = APR_BRIGADE_LAST(b);
+         e != APR_BRIGADE_SENTINEL(b);
+         e = APR_BUCKET_PREV(e)) {
 
-        /* handle CRLF after the chunk */
-        if (ctx->state == BODY_CHUNK_END
-                || ctx->state == BODY_CHUNK_END_LF) {
-            if (c == LF) {
-                if (strict && (ctx->state != BODY_CHUNK_END_LF)) {
-                    /*
-                     * CR missing before LF.
-                     */
-                    return APR_EINVAL;
-                }
-                ctx->state = BODY_CHUNK;
-            }
-            else if (c == CR && ctx->state == BODY_CHUNK_END) {
-                ctx->state = BODY_CHUNK_END_LF;
-            }
-            else {
-                /*
-                 * CRLF expected.
-                 */
-                return APR_EINVAL;
-            }
-            i++;
+        if (APR_BUCKET_IS_METADATA(e)) {
             continue;
         }
-
-        /* handle start of the chunk */
-        if (ctx->state == BODY_CHUNK) {
-            if (!apr_isxdigit(c)) {
-                /*
-                 * Detect invalid character at beginning. This also works for
-                 * empty chunk size lines.
-                 */
-                return APR_EINVAL;
-            }
-            else {
-                ctx->state = BODY_CHUNK_PART;
-            }
-            ctx->remaining = 0;
-            ctx->chunkbits = sizeof(apr_off_t) * 8;
-            ctx->chunk_used = 0;
-            ctx->chunk_bws = 0;
-        }
-
-        if (c == LF) {
-            if (strict && (ctx->state != BODY_CHUNK_LF)) {
-                /*
-                 * CR missing before LF.
-                 */
-                return APR_EINVAL;
-            }
-            if (ctx->remaining) {
-                ctx->state = BODY_CHUNK_DATA;
-            }
-            else {
-                ctx->state = BODY_CHUNK_TRAILER;
-            }
-        }
-        else if (ctx->state == BODY_CHUNK_LF) {
-            /*
-             * LF expected.
-             */
-            return APR_EINVAL;
-        }
-        else if (c == CR) {
-            ctx->state = BODY_CHUNK_LF;
-        }
-        else if (c == ';') {
-            ctx->state = BODY_CHUNK_EXT;
-        }
-        else if (ctx->state == BODY_CHUNK_EXT) {
-            /*
-             * Control chars (excluding tabs) are invalid.
-             * TODO: more precisely limit input
-             */
-            if (c != '\t' && apr_iscntrl(c)) {
-                return APR_EINVAL;
-            }
-        }
-        else if (c == ' ' || c == '\t') {
-            /* Be lenient up to 10 implied *LWS, a legacy of RFC 2616,
-             * and noted as errata to RFC7230;
-             * https://www.rfc-editor.org/errata_search.php?rfc=7230&eid=4667
-             */
-            ctx->state = BODY_CHUNK_CR;
-            if (++ctx->chunk_bws > 10) {
-                return APR_EINVAL;
-            }
-        }
-        else if (ctx->state == BODY_CHUNK_CR) {
-            /*
-             * ';', CR or LF expected.
-             */
-            return APR_EINVAL;
-        }
-        else if (ctx->state == BODY_CHUNK_PART) {
-            int xvalue;
-
-            /* ignore leading zeros */
-            if (!ctx->remaining && c == '0') {
-                i++;
-                continue;
-            }
-
-            ctx->chunkbits -= 4;
-            if (ctx->chunkbits < 0) {
-                /* overflow */
-                return APR_ENOSPC;
-            }
-
-            if (c >= '0' && c <= '9') {
-                xvalue = c - '0';
-            }
-            else if (c >= 'A' && c <= 'F') {
-                xvalue = c - 'A' + 0xa;
-            }
-            else if (c >= 'a' && c <= 'f') {
-                xvalue = c - 'a' + 0xa;
-            }
-            else {
-                /* bogus character */
-                return APR_EINVAL;
-            }
-
-            ctx->remaining = (ctx->remaining << 4) | xvalue;
-            if (ctx->remaining < 0) {
-                /* overflow */
-                return APR_ENOSPC;
-            }
+        rv = apr_bucket_read(e, &lineend, &len, APR_BLOCK_READ);
+        if (rv != APR_SUCCESS) {
+            return rv;
         }
-        else {
-            /* Should not happen */
-            return APR_EGENERAL;
+        if (len > 0) {
+            break;  /* we got the data we want */
         }
-
-        i++;
+        /* If we got a zero-length data bucket, we try the next one */
     }
-
-    /* sanity check */
-    ctx->chunk_used += len;
-    if (ctx->chunk_used < 0 || ctx->chunk_used > linelimit) {
-        return APR_ENOSPC;
+    /* We had no data in this brigade */
+    if (!len || e == APR_BRIGADE_SENTINEL(b)) {
+        return APR_EAGAIN;
     }
-
+    if (lineend[len - 1] != APR_ASCII_LF) {
+        return APR_EAGAIN;
+    }
+    /* Line is complete. So reset ctx->linesize for next round. */
+    ctx->linesize = 0;
     return APR_SUCCESS;
 }
 
-static apr_status_t read_chunked_trailers(http_ctx_t *ctx, ap_filter_t *f,
-                                          apr_bucket_brigade *b, int merge)
+static apr_status_t get_chunk_line(http_ctx_t *ctx, apr_bucket_brigade *b,
+                                   int linelimit)
 {
-    int rv;
-    apr_bucket *e;
-    request_rec *r = f->r;
-    apr_table_t *saved_headers_in = r->headers_in;
-    int saved_status = r->status;
-
-    r->status = HTTP_OK;
-    r->headers_in = r->trailers_in;
-    apr_table_clear(r->headers_in);
-    ap_get_mime_headers(r);
+    apr_size_t len;
+    int tmp_len;
+    apr_status_t rv;
 
-    if(r->status == HTTP_OK) {
-        r->status = saved_status;
-        e = apr_bucket_eos_create(f->c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(b, e);
-        ctx->eos_sent = 1;
-        rv = APR_SUCCESS;
+    tmp_len = sizeof(ctx->chunk_ln) - (ctx->pos - ctx->chunk_ln) - 1;
+    /* Saveguard ourselves against underflows */
+    if (tmp_len < 0) {
+        len = 0;
     }
     else {
-        const char *error_notes = apr_table_get(r->notes,
-                                                "error-notes");
-        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, 
-                      "Error while reading HTTP trailer: %i%s%s",
-                      r->status, error_notes ? ": " : "",
-                      error_notes ? error_notes : "");
-        rv = APR_EINVAL;
-    }
-
-    if(!merge) {
-        r->headers_in = saved_headers_in;
+        len = (apr_size_t) tmp_len;
     }
-    else {
-        r->headers_in = apr_table_overlay(r->pool, saved_headers_in,
-                r->trailers_in);
+    /*
+     * Check if there is space left in ctx->chunk_ln. If not, then either
+     * the chunk size is insane or we have chunk-extensions. Ignore both
+     * by discarding the remaining part of the line via
+     * get_remaining_chunk_line. Only bail out if the line is too long.
+     */
+    if (len > 0) {
+        rv = apr_brigade_flatten(b, ctx->pos, &len);
+        if (rv != APR_SUCCESS) {
+            return rv;
+        }
+        ctx->pos += len;
+        ctx->linesize += len;
+        *(ctx->pos) = '\0';
+        /*
+         * Check if we really got a full line. If yes the
+         * last char in the just read buffer must be LF.
+         * If not advance the buffer and return APR_EAGAIN.
+         * We do not start processing until we have the
+         * full line.
+         */
+        if (ctx->pos[-1] != APR_ASCII_LF) {
+            /* Check if the remaining data in the brigade has the LF */
+            return get_remaining_chunk_line(ctx, b, linelimit);
+        }
+        /* Line is complete. So reset ctx->pos for next round. */
+        ctx->pos = ctx->chunk_ln;
+        return APR_SUCCESS;
     }
-
-    return rv;
+    return get_remaining_chunk_line(ctx, b, linelimit);
 }
 
+
 /* This is the HTTP_INPUT filter for HTTP requests and responses from
  * proxied servers (mod_proxy).  It handles chunked and content-length
  * bodies.  This can only be inserted/used after the headers
  * are successfully parsed.
  */
 apr_status_t ap_http_filter(ap_filter_t *f, apr_bucket_brigade *b,
