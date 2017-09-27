     return (apr_table_get(r->headers_in, "Request-Range")
             || ((ua = apr_table_get(r->headers_in, "User-Agent"))
                 && ap_strstr_c(ua, "MSIE 3")));
 }
 
 #define BYTERANGE_FMT "%" APR_OFF_T_FMT "-%" APR_OFF_T_FMT "/%" APR_OFF_T_FMT
-#define PARTITION_ERR_FMT "apr_brigade_partition() failed " \
-                          "[%" APR_OFF_T_FMT ",%" APR_OFF_T_FMT "]"
+
+static apr_status_t copy_brigade_range(apr_bucket_brigade *bb,
+                                       apr_bucket_brigade *bbout,
+                                       apr_off_t start,
+                                       apr_off_t end)
+{
+    apr_bucket *first = NULL, *last = NULL, *out_first = NULL, *e;
+    apr_uint64_t pos = 0, off_first = 0, off_last = 0;
+    apr_status_t rv;
+    apr_uint64_t start64, end64;
+    apr_off_t pofft = 0;
+
+    /*
+     * Once we know that start and end are >= 0 convert everything to apr_uint64_t.
+     * See the comments in apr_brigade_partition why.
+     * In short apr_off_t (for values >= 0)and apr_size_t fit into apr_uint64_t.
+     */
+    start64 = (apr_uint64_t)start;
+    end64 = (apr_uint64_t)end;
+
+    if (start < 0 || end < 0 || start64 > end64)
+        return APR_EINVAL;
+
+    for (e = APR_BRIGADE_FIRST(bb);
+         e != APR_BRIGADE_SENTINEL(bb);
+         e = APR_BUCKET_NEXT(e))
+    {
+        apr_uint64_t elen64;
+        /* we know that no bucket has undefined length (-1) */
+        AP_DEBUG_ASSERT(e->length != (apr_size_t)(-1));
+        elen64 = (apr_uint64_t)e->length;
+        if (!first && (elen64 + pos > start64)) {
+            first = e;
+            off_first = pos;
+        }
+        if (elen64 + pos > end64) {
+            last = e;
+            off_last = pos;
+            break;
+        }
+        pos += elen64;
+    }
+    if (!first || !last)
+        return APR_EINVAL;
+
+    e = first;
+    while (1)
+    {
+        apr_bucket *copy;
+        AP_DEBUG_ASSERT(e != APR_BRIGADE_SENTINEL(bb));
+        rv = apr_bucket_copy(e, &copy);
+        if (rv != APR_SUCCESS) {
+            apr_brigade_cleanup(bbout);
+            return rv;
+        }
+
+        APR_BRIGADE_INSERT_TAIL(bbout, copy);
+        if (e == first) {
+            if (off_first != start64) {
+                rv = apr_bucket_split(copy, (apr_size_t)(start64 - off_first));
+                if (rv != APR_SUCCESS) {
+                    apr_brigade_cleanup(bbout);
+                    return rv;
+                }
+                out_first = APR_BUCKET_NEXT(copy);
+                APR_BUCKET_REMOVE(copy);
+                apr_bucket_destroy(copy);
+            }
+            else {
+                out_first = copy;
+            }
+        }
+        if (e == last) {
+            if (e == first) {
+                off_last += start64 - off_first;
+                copy = out_first;
+            }
+            if (end64 - off_last != (apr_uint64_t)e->length) {
+                rv = apr_bucket_split(copy, (apr_size_t)(end64 + 1 - off_last));
+                if (rv != APR_SUCCESS) {
+                    apr_brigade_cleanup(bbout);
+                    return rv;
+                }
+                copy = APR_BUCKET_NEXT(copy);
+                if (copy != APR_BRIGADE_SENTINEL(bbout)) {
+                    APR_BUCKET_REMOVE(copy);
+                    apr_bucket_destroy(copy);
+                }
+            }
+            break;
+        }
+        e = APR_BUCKET_NEXT(e);
+    }
+
+    AP_DEBUG_ASSERT(APR_SUCCESS == apr_brigade_length(bbout, 1, &pofft));
+    pos = (apr_uint64_t)pofft;
+    AP_DEBUG_ASSERT(pos == end64 - start64 + 1);
+    return APR_SUCCESS;
+}
+
+typedef struct indexes_t {
+    apr_off_t start;
+    apr_off_t end;
+} indexes_t;
+
+static int get_max_ranges(request_rec *r) {
+    core_dir_config *core_conf = (core_dir_config *)ap_get_module_config(r->per_dir_config,
+                                                                         &core_module);
+    if (core_conf->max_ranges >= 0 || core_conf->max_ranges == AP_MAXRANGES_UNLIMITED) {
+        return core_conf->max_ranges;
+    }
+
+    /* Any other negative val means the default */
+    return AP_DEFAULT_MAX_RANGES;
+}
+
+static apr_status_t send_416(ap_filter_t *f, apr_bucket_brigade *tmpbb)
+{
+    apr_bucket *e;
+    conn_rec *c = f->r->connection;
+    ap_remove_output_filter(f);
+    f->r->status = HTTP_OK;
+    e = ap_bucket_error_create(HTTP_RANGE_NOT_SATISFIABLE, NULL,
+                               f->r->pool, c->bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(tmpbb, e);
+    e = apr_bucket_eos_create(c->bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(tmpbb, e);
+    return ap_pass_brigade(f->next, tmpbb);
+}
 
 AP_CORE_DECLARE_NONSTD(apr_status_t) ap_byterange_filter(ap_filter_t *f,
                                                          apr_bucket_brigade *bb)
 {
-#define MIN_LENGTH(len1, len2) ((len1 > len2) ? len2 : len1)
     request_rec *r = f->r;
     conn_rec *c = r->connection;
-    byterange_ctx *ctx;
     apr_bucket *e;
     apr_bucket_brigade *bsend;
+    apr_bucket_brigade *tmpbb;
     apr_off_t range_start;
     apr_off_t range_end;
-    char *current;
     apr_off_t clength = 0;
     apr_status_t rv;
     int found = 0;
+    int num_ranges;
+    char *boundary = NULL;
+    char *bound_head = NULL;
+    apr_array_header_t *indexes;
+    indexes_t *idx;
+    int original_status;
+    int max_ranges = get_max_ranges(r);
+    int i;
 
-    /* Iterate through the brigade until reaching EOS or a bucket with
-     * unknown length. */
+    /*
+     * Iterate through the brigade until reaching EOS or a bucket with
+     * unknown length.
+     */
     for (e = APR_BRIGADE_FIRST(bb);
          (e != APR_BRIGADE_SENTINEL(bb) && !APR_BUCKET_IS_EOS(e)
           && e->length != (apr_size_t)-1);
          e = APR_BUCKET_NEXT(e)) {
         clength += e->length;
     }
 
-    /* Don't attempt to do byte range work if this brigade doesn't
+    /*
+     * Don't attempt to do byte range work if this brigade doesn't
      * contain an EOS, or if any of the buckets has an unknown length;
      * this avoids the cases where it is expensive to perform
-     * byteranging (i.e. may require arbitrary amounts of memory). */
+     * byteranging (i.e. may require arbitrary amounts of memory).
+     */
     if (!APR_BUCKET_IS_EOS(e) || clength <= 0) {
         ap_remove_output_filter(f);
         return ap_pass_brigade(f->next, bb);
     }
 
-    {
-        int num_ranges = ap_set_byterange(r);
+    original_status = r->status;
+    num_ranges = ap_set_byterange(r, clength, &indexes);
 
-        /* We have nothing to do, get out of the way. */
-        if (num_ranges == 0) {
-            ap_remove_output_filter(f);
-            return ap_pass_brigade(f->next, bb);
-        }
-
-        ctx = apr_pcalloc(r->pool, sizeof(*ctx));
-        ctx->num_ranges = num_ranges;
-        /* create a brigade in case we never call ap_save_brigade() */
-        ctx->bb = apr_brigade_create(r->pool, c->bucket_alloc);
-
-        if (ctx->num_ranges > 1) {
-            /* Is ap_make_content_type required here? */
-            const char *orig_ct = ap_make_content_type(r, r->content_type);
-            /* need APR_TIME_T_FMT_HEX */
-            ctx->boundary = apr_psprintf(r->pool, "%qx%lx",
-                                         r->request_time, (long) getpid());
-
-            ap_set_content_type(r, apr_pstrcat(r->pool, "multipart",
-                                               use_range_x(r) ? "/x-" : "/",
-                                               "byteranges; boundary=",
-                                               ctx->boundary, NULL));
-
-            ctx->bound_head = apr_pstrcat(r->pool,
-                                    CRLF "--", ctx->boundary,
-                                    CRLF "Content-type: ",
-                                    orig_ct,
-                                    CRLF "Content-range: bytes ",
-                                    NULL);
-            ap_xlate_proto_to_ascii(ctx->bound_head, strlen(ctx->bound_head));
-        }
+    /* We have nothing to do, get out of the way. */
+    if (num_ranges == 0 || (max_ranges >= 0 && num_ranges > max_ranges)) {
+        r->status = original_status;
+        ap_remove_output_filter(f);
+        return ap_pass_brigade(f->next, bb);
     }
 
     /* this brigade holds what we will be sending */
     bsend = apr_brigade_create(r->pool, c->bucket_alloc);
 
-    while ((current = ap_getword(r->pool, &r->range, ','))
-           && (rv = parse_byterange(current, clength, &range_start,
-                                    &range_end))) {
-        apr_bucket *e2;
-        apr_bucket *ec;
+    if (num_ranges < 0)
+        return send_416(f, bsend);
+  
+    if (num_ranges > 1) {
+        /* Is ap_make_content_type required here? */
+        const char *orig_ct = ap_make_content_type(r, r->content_type);
+        boundary = apr_psprintf(r->pool, "%" APR_UINT64_T_HEX_FMT "%lx",
+                                (apr_uint64_t)r->request_time, c->id);
+
+        ap_set_content_type(r, apr_pstrcat(r->pool, "multipart",
+                                           use_range_x(r) ? "/x-" : "/",
+                                           "byteranges; boundary=",
+                                           boundary, NULL));
+
+        bound_head = apr_pstrcat(r->pool,
+                                 CRLF "--", boundary,
+                                 CRLF "Content-type: ",
+                                 orig_ct,
+                                 CRLF "Content-range: bytes ",
+                                 NULL);
+        ap_xlate_proto_to_ascii(bound_head, strlen(bound_head));
+    }
 
-        if (rv == -1) {
-            continue;
-        }
+    tmpbb = apr_brigade_create(r->pool, c->bucket_alloc);
 
-        /* these calls to apr_brigade_partition() should theoretically
-         * never fail because of the above call to apr_brigade_length(),
-         * but what the heck, we'll check for an error anyway */
-        if ((rv = apr_brigade_partition(bb, range_start, &ec)) != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                          PARTITION_ERR_FMT, range_start, clength);
-            continue;
-        }
-        if ((rv = apr_brigade_partition(bb, range_end+1, &e2)) != APR_SUCCESS) {
+    idx = (indexes_t *)indexes->elts;
+    for (i = 0; i < indexes->nelts; i++, idx++) {
+        range_start = idx->start;
+        range_end = idx->end;
+
+        rv = copy_brigade_range(bb, tmpbb, range_start, range_end);
+        if (rv != APR_SUCCESS ) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                          PARTITION_ERR_FMT, range_end+1, clength);
+                          "copy_brigade_range() failed [%" APR_OFF_T_FMT
+                          "-%" APR_OFF_T_FMT ",%" APR_OFF_T_FMT "]",
+                          range_start, range_end, clength);
             continue;
         }
-
         found = 1;
 
-        /* For single range requests, we must produce Content-Range header.
+        /*
+         * For single range requests, we must produce Content-Range header.
          * Otherwise, we need to produce the multipart boundaries.
          */
-        if (ctx->num_ranges == 1) {
+        if (num_ranges == 1) {
             apr_table_setn(r->headers_out, "Content-Range",
                            apr_psprintf(r->pool, "bytes " BYTERANGE_FMT,
                                         range_start, range_end, clength));
         }
         else {
             char *ts;
 
-            e = apr_bucket_pool_create(ctx->bound_head, strlen(ctx->bound_head),
+            e = apr_bucket_pool_create(bound_head, strlen(bound_head),
                                        r->pool, c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bsend, e);
 
             ts = apr_psprintf(r->pool, BYTERANGE_FMT CRLF CRLF,
                               range_start, range_end, clength);
             ap_xlate_proto_to_ascii(ts, strlen(ts));
             e = apr_bucket_pool_create(ts, strlen(ts), r->pool,
                                        c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bsend, e);
         }
 
-        do {
-            apr_bucket *foo;
-            const char *str;
-            apr_size_t len;
-
-            if (apr_bucket_copy(ec, &foo) != APR_SUCCESS) {
-                /* this shouldn't ever happen due to the call to
-                 * apr_brigade_length() above which normalizes
-                 * indeterminate-length buckets.  just to be sure,
-                 * though, this takes care of uncopyable buckets that
-                 * do somehow manage to slip through.
-                 */
-                /* XXX: check for failure? */
-                apr_bucket_read(ec, &str, &len, APR_BLOCK_READ);
-                apr_bucket_copy(ec, &foo);
-            }
-            APR_BRIGADE_INSERT_TAIL(bsend, foo);
-            ec = APR_BUCKET_NEXT(ec);
-        } while (ec != e2);
+        APR_BRIGADE_CONCAT(bsend, tmpbb);
+        if (i && !(i & 0x1F)) {
+            /*
+             * Every now and then, pass what we have down the filter chain.
+             * In this case, the content-length filter cannot calculate and
+             * set the content length and we must remove any Content-Length
+             * header already present.
+             */
+            apr_table_unset(r->headers_out, "Content-Length");
+            if ((rv = ap_pass_brigade(f->next, bsend)) != APR_SUCCESS)
+                return rv;
+            apr_brigade_cleanup(bsend);
+        }
     }
 
     if (found == 0) {
-        ap_remove_output_filter(f);
-        r->status = HTTP_OK;
         /* bsend is assumed to be empty if we get here. */
-        e = ap_bucket_error_create(HTTP_RANGE_NOT_SATISFIABLE, NULL,
-                                   r->pool, c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(bsend, e);
-        e = apr_bucket_eos_create(c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(bsend, e);
-        return ap_pass_brigade(f->next, bsend);
+        return send_416(f, bsend);
     }
 
-    if (ctx->num_ranges > 1) {
+    if (num_ranges > 1) {
         char *end;
 
         /* add the final boundary */
-        end = apr_pstrcat(r->pool, CRLF "--", ctx->boundary, "--" CRLF, NULL);
+        end = apr_pstrcat(r->pool, CRLF "--", boundary, "--" CRLF, NULL);
         ap_xlate_proto_to_ascii(end, strlen(end));
         e = apr_bucket_pool_create(end, strlen(end), r->pool, c->bucket_alloc);
         APR_BRIGADE_INSERT_TAIL(bsend, e);
     }
 
     e = apr_bucket_eos_create(c->bucket_alloc);
     APR_BRIGADE_INSERT_TAIL(bsend, e);
 
     /* we're done with the original content - all of our data is in bsend. */
-    apr_brigade_destroy(bb);
+    apr_brigade_cleanup(bb);
+    apr_brigade_destroy(tmpbb);
 
     /* send our multipart output */
     return ap_pass_brigade(f->next, bsend);
 }
 
-static int ap_set_byterange(request_rec *r)
+/* for consistency with 2.2 code which uses apr_strtoff()
+ * (missing from apr 0.9)
+ */
+static apr_status_t strtoff(apr_off_t *offset, const char *nptr,
+                           char **endptr, int base)
+{
+   errno = 0;
+   if (sizeof(apr_off_t) == 4) {
+       *offset = strtol(nptr, endptr, base);
+   }
+   else {
+       *offset = apr_strtoi64(nptr, endptr, base);
+   }
+   return APR_FROM_OS_ERROR(errno);
+}
+
+static int ap_set_byterange(request_rec *r, apr_off_t clength,
+                            apr_array_header_t **indexes)
 {
     const char *range;
     const char *if_range;
     const char *match;
     const char *ct;
-    int num_ranges;
+    char *cur;
+    int num_ranges = 0, unsatisfiable = 0;
+    apr_off_t sum_lengths = 0;
+    indexes_t *idx;
+    int ranges = 1;
+    const char *it;
 
     if (r->assbackwards) {
         return 0;
     }
 
-    /* Check for Range request-header (HTTP/1.1) or Request-Range for
+    /*
+     * Check for Range request-header (HTTP/1.1) or Request-Range for
      * backwards-compatibility with second-draft Luotonen/Franks
      * byte-ranges (e.g. Netscape Navigator 2-3).
      *
      * We support this form, with Request-Range, and (farther down) we
      * send multipart/x-byteranges instead of multipart/byteranges for
      * Request-Range based requests to work around a bug in Netscape
