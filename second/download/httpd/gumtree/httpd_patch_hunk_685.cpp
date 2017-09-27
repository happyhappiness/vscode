         APR_BRIGADE_CONCAT(ctx->proc_bb, newbb);
     }
 
     return APR_SUCCESS;
 }
 
+
+/* Filter to inflate for a content-transforming proxy.  */
+static apr_status_t inflate_out_filter(ap_filter_t *f,
+                                      apr_bucket_brigade *bb)
+{
+    int zlib_method;
+    int zlib_flags;
+    int deflate_init = 1;
+    apr_bucket *bkt;
+    request_rec *r = f->r;
+    deflate_ctx *ctx = f->ctx;
+    int zRC;
+    apr_status_t rv;
+    deflate_filter_config *c;
+
+    /* Do nothing if asked to filter nothing. */
+    if (APR_BRIGADE_EMPTY(bb)) {
+        return APR_SUCCESS;
+    }
+
+    c = ap_get_module_config(r->server->module_config, &deflate_module);
+
+    if (!ctx) {
+        int found = 0;
+        char *token;
+        const char *encoding;
+
+        /* only work on main request/no subrequests */
+        if (!ap_is_initial_req(r)) {
+            ap_remove_output_filter(f);
+            return ap_pass_brigade(f->next, bb);
+        }
+
+        /* Let's see what our current Content-Encoding is.
+         * If gzip is present, don't gzip again.  (We could, but let's not.)
+         */
+        encoding = apr_table_get(r->headers_out, "Content-Encoding");
+        if (encoding) {
+            const char *tmp = encoding;
+
+            token = ap_get_token(r->pool, &tmp, 0);
+            while (token && token[0]) {
+                if (!strcasecmp(token, "gzip")) {
+                    found = 1;
+                    break;
+                }
+                /* Otherwise, skip token */
+                tmp++;
+                token = ap_get_token(r->pool, &tmp, 0);
+            }
+        }
+
+        if (found == 0) {
+            ap_remove_output_filter(f);
+            return ap_pass_brigade(f->next, bb);
+        }
+        apr_table_unset(r->headers_out, "Content-Encoding");
+
+        /* No need to inflate HEAD or 204/304 */
+        if (APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(bb))) {
+            ap_remove_output_filter(f);
+            return ap_pass_brigade(f->next, bb);
+        }
+
+
+        f->ctx = ctx = apr_pcalloc(f->r->pool, sizeof(*ctx));
+        ctx->proc_bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
+        ctx->buffer = apr_palloc(r->pool, c->bufferSize);
+
+
+        zRC = inflateInit2(&ctx->stream, c->windowSize);
+
+        if (zRC != Z_OK) {
+            f->ctx = NULL;
+            inflateEnd(&ctx->stream);
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                          "unable to init Zlib: "
+                          "inflateInit2 returned %d: URL %s",
+                          zRC, r->uri);
+            ap_remove_output_filter(f);
+            return ap_pass_brigade(f->next, bb);
+        }
+
+        /* initialize deflate output buffer */
+        ctx->stream.next_out = ctx->buffer;
+        ctx->stream.avail_out = c->bufferSize;
+
+        deflate_init = 0;
+    }
+
+    for (bkt = APR_BRIGADE_FIRST(bb);
+         bkt != APR_BRIGADE_SENTINEL(bb);
+         bkt = APR_BUCKET_NEXT(bkt))
+    {
+        const char *data;
+        apr_size_t len;
+
+        /* If we actually see the EOS, that means we screwed up! */
+        /* no it doesn't - not in a HEAD or 204/304 */
+        if (APR_BUCKET_IS_EOS(bkt)) {
+            inflateEnd(&ctx->stream);
+            return ap_pass_brigade(f->next, bb);
+        }
+
+        if (APR_BUCKET_IS_FLUSH(bkt)) {
+            apr_bucket *tmp_heap;
+            zRC = inflate(&(ctx->stream), Z_SYNC_FLUSH);
+            if (zRC != Z_OK) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                              "Inflate error %d on flush", zRC);
+                inflateEnd(&ctx->stream);
+                return APR_EGENERAL;
+            }
+
+            ctx->stream.next_out = ctx->buffer;
+            len = c->bufferSize - ctx->stream.avail_out;
+
+            ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
+            tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
+                                             NULL, f->c->bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
+            ctx->stream.avail_out = c->bufferSize;
+
+            /* Move everything to the returning brigade. */
+            APR_BUCKET_REMOVE(bkt);
+            break;
+        }
+
+        /* read */
+        apr_bucket_read(bkt, &data, &len, APR_BLOCK_READ);
+
+        /* first bucket contains zlib header */
+        if (!deflate_init++) {
+            if (len < 10) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                              "Insufficient data for inflate");
+                return APR_EGENERAL;
+            }
+            else  {
+                zlib_method = data[2];
+                zlib_flags = data[3];
+                if (zlib_method != Z_DEFLATED) {
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                                  "inflate: data not deflated!");
+                    ap_remove_output_filter(f);
+                    return ap_pass_brigade(f->next, bb);
+                }
+                if (data[0] != deflate_magic[0] ||
+                    data[1] != deflate_magic[1] ||
+                    (zlib_flags & RESERVED) != 0) {
+                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                                      "inflate: bad header");
+                    return APR_EGENERAL ;
+                }
+                data += 10 ;
+                len -= 10 ;
+           }
+           if (zlib_flags & EXTRA_FIELD) {
+               unsigned int bytes = (unsigned int)(data[0]);
+               bytes += ((unsigned int)(data[1])) << 8;
+               bytes += 2;
+               if (len < bytes) {
+                   ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                                 "inflate: extra field too big (not "
+                                 "supported)");
+                   return APR_EGENERAL;
+               }
+               data += bytes;
+               len -= bytes;
+           }
+           if (zlib_flags & ORIG_NAME) {
+               while (len-- && *data++);
+           }
+           if (zlib_flags & COMMENT) {
+               while (len-- && *data++);
+           }
+           if (zlib_flags & HEAD_CRC) {
+                len -= 2;
+                data += 2;
+           }
+        }
+
+        /* pass through zlib inflate. */
+        ctx->stream.next_in = (unsigned char *)data;
+        ctx->stream.avail_in = len;
+
+        zRC = Z_OK;
+
+        while (ctx->stream.avail_in != 0) {
+            if (ctx->stream.avail_out == 0) {
+                apr_bucket *tmp_heap;
+                ctx->stream.next_out = ctx->buffer;
+                len = c->bufferSize - ctx->stream.avail_out;
+
+                ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
+                tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
+                                                  NULL, f->c->bucket_alloc);
+                APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
+                ctx->stream.avail_out = c->bufferSize;
+            }
+
+            zRC = inflate(&ctx->stream, Z_NO_FLUSH);
+
+            if (zRC == Z_STREAM_END) {
+                break;
+            }
+
+            if (zRC != Z_OK) {
+                    inflateEnd(&ctx->stream);
+                    return APR_EGENERAL;
+            }
+        }
+        if (zRC == Z_STREAM_END) {
+            apr_bucket *tmp_heap, *eos;
+
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                          "Zlib: Inflated %ld to %ld : URL %s",
+                          ctx->stream.total_in, ctx->stream.total_out,
+                          r->uri);
+
+            len = c->bufferSize - ctx->stream.avail_out;
+
+            ctx->crc = crc32(ctx->crc, (const Bytef *)ctx->buffer, len);
+            tmp_heap = apr_bucket_heap_create((char *)ctx->buffer, len,
+                                              NULL, f->c->bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, tmp_heap);
+            ctx->stream.avail_out = c->bufferSize;
+
+            /* Is the remaining 8 bytes already in the avail stream? */
+            if (ctx->stream.avail_in >= 8) {
+                unsigned long compCRC, compLen;
+                compCRC = getLong(ctx->stream.next_in);
+                if (ctx->crc != compCRC) {
+                    inflateEnd(&ctx->stream);
+                    return APR_EGENERAL;
+                }
+                ctx->stream.next_in += 4;
+                compLen = getLong(ctx->stream.next_in);
+                if (ctx->stream.total_out != compLen) {
+                    inflateEnd(&ctx->stream);
+                    return APR_EGENERAL;
+                }
+            }
+            else {
+                /* FIXME: We need to grab the 8 verification bytes
+                 * from the wire! */
+                inflateEnd(&ctx->stream);
+                return APR_EGENERAL;
+            }
+
+            inflateEnd(&ctx->stream);
+
+            eos = apr_bucket_eos_create(f->c->bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(ctx->proc_bb, eos);
+            break;
+        }
+
+    }
+
+    rv = ap_pass_brigade(f->next, ctx->proc_bb);
+    apr_brigade_cleanup(ctx->proc_bb);
+    return rv ;
+}
+
 static void register_hooks(apr_pool_t *p)
 {
     ap_register_output_filter(deflateFilterName, deflate_out_filter, NULL,
                               AP_FTYPE_CONTENT_SET);
+    ap_register_output_filter("INFLATE", inflate_out_filter, NULL,
+                              AP_FTYPE_RESOURCE-1);
     ap_register_input_filter(deflateFilterName, deflate_in_filter, NULL,
                               AP_FTYPE_CONTENT_SET);
 }
 
 static const command_rec deflate_filter_cmds[] = {
     AP_INIT_TAKE12("DeflateFilterNote", deflate_set_note, NULL, RSRC_CONF,
