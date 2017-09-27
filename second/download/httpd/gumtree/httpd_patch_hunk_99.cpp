 {
     buffer->value = in;
     buffer->length = inl;
     return inl;
 }
 
-/*
- * this is the function called by SSL_read()
+/* This function will read from a brigade and discard the read buckets as it
+ * proceeds.  It will read at most *len bytes.
  */
-#define BIO_bucket_in_ptr(bio) (BIO_bucket_in_t *)bio->ptr
-
-static int bio_bucket_in_read(BIO *bio, char *in, int inl)
+static apr_status_t brigade_consume(apr_bucket_brigade *bb,
+                                    apr_read_type_e block,
+                                    char *c, apr_size_t *len)
 {
-    BIO_bucket_in_t *inbio = BIO_bucket_in_ptr(bio);
-    SSLConnRec *sslconn = myConnConfig(inbio->f->c);
-    int len = 0;
-
-    /* XXX: flush here only required for SSLv2;
-     * OpenSSL calls BIO_flush() at the appropriate times for
-     * the other protocols.
-     */
-    if ((SSL_version(inbio->ssl) == SSL2_VERSION) || sslconn->is_proxy) {
-        BIO_bucket_flush(inbio->wbio);
-    }
-
-    inbio->rc = APR_SUCCESS;
-    
-    /* first use data already read from socket if any */
-    if ((len = char_buffer_read(&inbio->cbuf, in, inl))) {
-        if ((len <= inl) || inbio->mode == AP_MODE_GETLINE) {
-            return len;
-        }
-        inl -= len;
-    }
-
-    while (1) {
-        const char *buf;
-        apr_size_t buf_len = 0;
-
-        if (inbio->bucket) {
-            /* all of the data in this bucket has been read,
-             * so we can delete it now.
-             */
-            apr_bucket_delete(inbio->bucket);
-            inbio->bucket = NULL;
+    apr_size_t actual = 0;
+    apr_status_t status = APR_SUCCESS;
+ 
+    while (!APR_BRIGADE_EMPTY(bb)) {
+        apr_bucket *b = APR_BRIGADE_FIRST(bb);
+        const char *str;
+        apr_size_t str_len;
+        apr_size_t consume;
+
+        /* Justin points out this is an http-ism that might
+         * not fit if brigade_consume is added to APR.  Perhaps
+         * apr_bucket_read(eos_bucket) should return APR_EOF?
+         * Then this becomes mainline instead of a one-off.
+         */
+        if (APR_BUCKET_IS_EOS(b)) {
+            status = APR_EOF;
+            break;
         }
 
-        if (APR_BRIGADE_EMPTY(inbio->bb)) {
-            /* We will always call with READBYTES even if the user wants
-             * GETLINE.
-             */
-            inbio->rc = ap_get_brigade(inbio->f->next, inbio->bb,
-                                       AP_MODE_READBYTES, inbio->block, 
-                                       inl);
-
-            if ((inbio->rc != APR_SUCCESS) || APR_BRIGADE_EMPTY(inbio->bb))
-            {
-                break;
+        /* The reason I'm not offering brigade_consume yet
+         * across to apr-util is that the following call
+         * illustrates how borked that API really is.  For
+         * this sort of case (caller provided buffer) it
+         * would be much more trivial for apr_bucket_consume
+         * to do all the work that follows, based on the
+         * particular characteristics of the bucket we are 
+         * consuming here.
+         */
+        status = apr_bucket_read(b, &str, &str_len, block);
+        
+        if (status != APR_SUCCESS) {
+            if (APR_STATUS_IS_EOF(status)) {
+                /* This stream bucket was consumed */
+                apr_bucket_delete(b);
+                continue;
             }
+            break;
         }
 
-        inbio->bucket = APR_BRIGADE_FIRST(inbio->bb);
+        if (str_len > 0) {
+            /* Do not block once some data has been consumed */
+            block = APR_NONBLOCK_READ;
 
-        inbio->rc = apr_bucket_read(inbio->bucket,
-                                    &buf, &buf_len, inbio->block);
+            /* Assure we don't overflow. */
+            consume = (str_len + actual > *len) ? *len - actual : str_len;
 
-        if (inbio->rc != APR_SUCCESS) {
-            apr_bucket_delete(inbio->bucket);
-            inbio->bucket = NULL;
-            return len;
-        }
+            memcpy(c, str, consume);
 
-        if (buf_len) {
-            /* Protected against len > MAX_INT 
-             */
-            if ((len + (int)buf_len) >= inl || (int)buf_len < 0) {
-                /* we have enough to fill the buffer.
-                 * append if we have already written to the buffer.
-                 */
-                int nibble = inl - len;
-                char *value = (char *)buf+nibble;
+            c += consume;
+            actual += consume;
 
-                int length = buf_len - nibble;
-                memcpy(in + len, buf, nibble);
-
-                char_buffer_write(&inbio->cbuf, value, length);
-                len += nibble;
-
-                break;
+            if (consume >= b->length) {
+                /* This physical bucket was consumed */
+                apr_bucket_delete(b);
             }
             else {
-                /* not enough data,
-                 * save what we have and try to read more.
-                 */
-                memcpy(in + len, buf, buf_len);
-                len += buf_len;
+                /* Only part of this physical bucket was consumed */
+                b->start += consume;
+                b->length -= consume;
             }
         }
+        else if (b->length == 0) {
+            apr_bucket_delete(b);
+        }
 
-        if (inbio->mode == AP_MODE_GETLINE) {
-            /* only read from the socket once in getline mode.
-             * since callers buffer size is likely much larger than
-             * the request headers.  caller can always come back for more
-             * if first read didn't get all the headers.
-             */
+        /* This could probably be actual == *len, but be safe from stray
+         * photons. */
+        if (actual >= *len) {
             break;
         }
     }
 
-    return len;
+    *len = actual;
+    return status;
 }
 
-static BIO_METHOD bio_bucket_in_method = {
-    BIO_TYPE_MEM,
-    "APR input bucket brigade",
-    NULL,                       /* write is never called */
-    bio_bucket_in_read,
-    NULL,                       /* puts is never called */
-    NULL,                       /* gets is never called */
-    NULL,                       /* ctrl is never called */
-    bio_bucket_new,
-    bio_bucket_free,
-#ifdef OPENSSL_VERSION_NUMBER
-    NULL /* sslc does not have the callback_ctrl field */
-#endif
-};
-
-static BIO_METHOD *BIO_s_in_bucket(void)
+/*
+ * this is the function called by SSL_read()
+ */
+static int bio_filter_in_read(BIO *bio, char *in, int inl)
 {
-    return &bio_bucket_in_method;
-}
+    bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)(bio->ptr);
+    apr_read_type_e block = inctx->block;
+    SSLConnRec *sslconn = myConnConfig(inctx->f->c);
 
-static const char ssl_io_filter[] = "SSL/TLS Filter";
-
-static int ssl_io_hook_read(SSL *ssl, char *buf, int len)
-{
-    int rc;
+    inctx->rc = APR_SUCCESS;
 
-    if (ssl == NULL) {
-        return -1;
-    }
-
-    rc = SSL_read(ssl, buf, len);
-
-    if (rc <= 0) {
-        int ssl_err = SSL_get_error(ssl, rc);
+    /* OpenSSL catches this case, so should we. */
+    if (!in)
+        return 0;
 
-        if (ssl_err == SSL_ERROR_WANT_READ) {
-            /*
-             * Simulate an EINTR in case OpenSSL wants to read more.
-             * (This is usually the case when the client forces an SSL
-             * renegotation which is handled implicitly by OpenSSL.)
-             */
-            errno = EINTR;
-            rc = 0; /* non fatal error */
-        }
-        else if (ssl_err == SSL_ERROR_SSL) {
-            /*
-             * Log SSL errors
-             */
-            conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
-                    "SSL error on reading data");
-            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
+    /* XXX: flush here only required for SSLv2;
+     * OpenSSL calls BIO_flush() at the appropriate times for
+     * the other protocols.
+     */
+    if ((SSL_version(inctx->ssl) == SSL2_VERSION) || sslconn->is_proxy) {
+        if (bio_filter_out_flush(inctx->bio_out) < 0) {
+            bio_filter_out_ctx_t *outctx = 
+                   (bio_filter_out_ctx_t *)(inctx->bio_out->ptr);
+            inctx->rc = outctx->rc;
+            return -1;
         }
     }
 
-    return rc;
-}
-
-static int ssl_io_hook_write(SSL *ssl, unsigned char *buf, int len)
-{
-    int rc;
+    BIO_clear_retry_flags(bio);
 
-    if (ssl == NULL) {
+    if (!inctx->bb) {
+        inctx->rc = APR_EOF;
         return -1;
     }
 
-    rc = SSL_write(ssl, buf, len);
+    if (APR_BRIGADE_EMPTY(inctx->bb)) {
 
-    if (rc < 0) {
-        int ssl_err = SSL_get_error(ssl, rc);
+        inctx->rc = ap_get_brigade(inctx->f->next, inctx->bb,
+                                   AP_MODE_READBYTES, block, 
+                                   inl);
 
-        if (ssl_err == SSL_ERROR_WANT_WRITE) {
-            /*
-             * Simulate an EINTR in case OpenSSL wants to write more.
-             */
-            errno = EINTR;
-        }
-        else if (ssl_err == SSL_ERROR_SSL) {
-            /*
-             * Log SSL errors
-             */
-            conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
-                    "SSL error on writing data");
-            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
-        }
-        /*
-         * XXX - Just trying to reflect the behaviour in 
-         * openssl_state_machine.c [mod_tls]. TBD
+        /* Not a problem, there was simply no data ready yet.
          */
-        rc = 0;
-    }
-    return rc;
-}
-
-static apr_status_t ssl_filter_write(ap_filter_t *f,
-                                     const char *data,
-                                     apr_size_t len)
-{
-    SSLFilterRec *ctx = f->ctx;
-    apr_size_t n;
-
-    /* write SSL */
-    n = ssl_io_hook_write(ctx->pssl, (unsigned char *)data, len);
-
-    if (n != len) {
-        conn_rec *c = f->c;
-        char *reason = "reason unknown";
-
-        /* XXX: probably a better way to determine this */
-        if (SSL_total_renegotiations(ctx->pssl)) {
-            reason = "likely due to failed renegotiation";
+        if (APR_STATUS_IS_EAGAIN(inctx->rc) || APR_STATUS_IS_EINTR(inctx->rc)
+               || (inctx->rc == APR_SUCCESS && APR_BRIGADE_EMPTY(inctx->bb))) {
+            BIO_set_retry_read(bio);
+            return 0;
         }
 
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
-                "failed to write %d of %d bytes (%s)",
-                n > 0 ? len - n : len, len, reason);
-
-        return APR_EINVAL;
+        if (inctx->rc != APR_SUCCESS) {
+            /* Unexpected errors discard the brigade */
+            apr_brigade_cleanup(inctx->bb);
+            inctx->bb = NULL;
+            return -1;
+        }
     }
 
-    return APR_SUCCESS;
-}
-
-static apr_status_t ssl_io_filter_Output(ap_filter_t *f,
-                                         apr_bucket_brigade *bb)
-{
-    apr_status_t status = APR_SUCCESS;
-    SSLFilterRec *ctx = f->ctx;
+    inctx->rc = brigade_consume(inctx->bb, block, in, &inl);
 
-    if (!ctx->pssl) {
-        /* ssl_abort() has been called */
-        return ap_pass_brigade(f->next, bb);
+    if (inctx->rc == APR_SUCCESS) {
+        return inl;
     }
 
-    if ((status = ssl_hook_process_connection(ctx)) != APR_SUCCESS) {
-        return status;
+    if (APR_STATUS_IS_EAGAIN(inctx->rc) 
+            || APR_STATUS_IS_EINTR(inctx->rc)) {
+        BIO_set_retry_read(bio);
+        return inl;
     }
+        
+    /* Unexpected errors and APR_EOF clean out the brigade.
+     * Subsequent calls will return APR_EOF.
+     */
+    apr_brigade_cleanup(inctx->bb);
+    inctx->bb = NULL;
 
-    while (!APR_BRIGADE_EMPTY(bb)) {
-        apr_bucket *bucket = APR_BRIGADE_FIRST(bb);
-
-        /* If it is a flush or EOS, we need to pass this down. 
-         * These types do not require translation by OpenSSL.  
+    if (APR_STATUS_IS_EOF(inctx->rc) && inl) {
+        /* Provide the results of this read pass,
+         * without resetting the BIO retry_read flag
          */
-        if (APR_BUCKET_IS_EOS(bucket) || APR_BUCKET_IS_FLUSH(bucket)) {
-            if ((status = BIO_bucket_flush(ctx->pbioWrite)) != APR_SUCCESS) {
-                return status;
-            }
-
-            if (APR_BUCKET_IS_EOS(bucket)) {
-                /* By definition, nothing can come after EOS.
-                 * which also means we can pass the rest of this brigade
-                 * without creating a new one since it only contains the
-                 * EOS bucket.
-                 */
+        return inl;
+    }
 
-                if ((status = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
-                    return status;
-                }
-                break;
-            }
-            else {
-                /* BIO_bucket_flush() already passed down a flush bucket
-                 * if there was any data to be flushed.
-                 */
-                apr_bucket_delete(bucket);
-            }
-        }
-        else {
-            /* read filter */
-            const char *data;
-            apr_size_t len;
+    return -1;
+}
 
-            apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);
-            status = ssl_filter_write(f, data, len);
-            apr_bucket_delete(bucket);
 
-            if (status != APR_SUCCESS) {
-                break;
-            }
-        }
-    }
+static BIO_METHOD bio_filter_in_method = {
+    BIO_TYPE_MEM,
+    "APR input filter",
+    NULL,                       /* write is never called */
+    bio_filter_in_read,
+    NULL,                       /* puts is never called */
+    NULL,                       /* gets is never called */
+    NULL,                       /* ctrl is never called */
+    bio_filter_create,
+    bio_filter_destroy,
+#ifdef OPENSSL_VERSION_NUMBER
+    NULL /* sslc does not have the callback_ctrl field */
+#endif
+};
 
-    return status;
-}
 
-/*
- * ctx->cbuf is leftover plaintext from ssl_io_input_getline,
- * use what we have there first if any,
- * then go for more by calling ssl_io_hook_read.
- */
-static apr_status_t ssl_io_input_read(ssl_io_input_ctx_t *ctx,
+static apr_status_t ssl_io_input_read(bio_filter_in_ctx_t *inctx,
                                       char *buf,
                                       apr_size_t *len)
 {
     apr_size_t wanted = *len;
     apr_size_t bytes = 0;
     int rc;
 
     *len = 0;
 
-    if ((bytes = char_buffer_read(&ctx->cbuf, buf, wanted))) {
+    /* If we have something leftover from last time, try that first. */
+    if ((bytes = char_buffer_read(&inctx->cbuf, buf, wanted))) {
         *len = bytes;
-        if (ctx->inbio.mode == AP_MODE_SPECULATIVE) {
+        if (inctx->mode == AP_MODE_SPECULATIVE) {
             /* We want to rollback this read. */
-            ctx->cbuf.value -= bytes;
-            ctx->cbuf.length += bytes;
+            inctx->cbuf.value -= bytes;
+            inctx->cbuf.length += bytes;
             return APR_SUCCESS;
-        } 
-        if ((*len >= wanted) || ctx->inbio.mode == AP_MODE_GETLINE) {
+        }
+        /* This could probably be *len == wanted, but be safe from stray
+         * photons.
+         */
+        if (*len >= wanted) {
             return APR_SUCCESS;
         }
+        if (inctx->mode == AP_MODE_GETLINE) {
+            if (memchr(buf, APR_ASCII_LF, *len)) {
+                return APR_SUCCESS;
+            }
+        }
+        else {
+            /* Down to a nonblock pattern as we have some data already
+             */
+            inctx->block = APR_NONBLOCK_READ;
+        }
     }
 
-    rc = ssl_io_hook_read(ctx->frec->pssl, buf + bytes, wanted - bytes);
+    while (1) {
 
-    if (rc > 0) {
-        *len += rc;
-        if (ctx->inbio.mode == AP_MODE_SPECULATIVE) {
-            char_buffer_write(&ctx->cbuf, buf, rc);
+        if (!inctx->filter_ctx->pssl) {
+            break;
         }
-    }
-    else if ((rc == 0) && (errno != EINTR)) {
-        /* something other than SSL_ERROR_WANT_READ */
-        return APR_EOF;
-    }
-    else if ((rc == -1) && (ctx->inbio.rc == APR_SUCCESS)) {
-        /*
-         * bucket read from socket was successful,
-         * but there was an error within the ssl runtime.
+
+        /* SSL_read may not read because we haven't taken enough data
+         * from the stack.  This is where we want to consider all of
+         * the blocking and SPECULATIVE semantics
          */
-        return APR_EGENERAL;
-    }
+        rc = SSL_read(inctx->filter_ctx->pssl, buf + bytes, wanted - bytes);
 
-    return ctx->inbio.rc;
+        if (rc > 0) {
+            *len += rc;
+            if (inctx->mode == AP_MODE_SPECULATIVE) {
+                /* We want to rollback this read. */
+                char_buffer_write(&inctx->cbuf, buf, rc);
+            }
+            return inctx->rc;
+        }
+        else if (rc == 0) {
+            /* If EAGAIN, we will loop given a blocking read,
+             * otherwise consider ourselves at EOF.
+             */
+            if (APR_STATUS_IS_EAGAIN(inctx->rc)
+                    || APR_STATUS_IS_EINTR(inctx->rc)) {
+                /* Already read something, return APR_SUCCESS instead. 
+                 * On win32 in particular, but perhaps on other kernels,
+                 * a blocking call isn't 'always' blocking.
+                 */
+                if (*len > 0) {
+                    inctx->rc = APR_SUCCESS;
+                    break;
+                }
+                if (inctx->block == APR_NONBLOCK_READ) {
+                    break;
+                }
+            }
+            else {
+                if (*len > 0) {
+                    inctx->rc = APR_SUCCESS;
+                }
+                else {
+                    inctx->rc = APR_EOF;
+                }
+                break;
+            }
+        }
+        else /* (rc < 0) */ {
+            int ssl_err = SSL_get_error(inctx->filter_ctx->pssl, rc);
+            conn_rec *c = (conn_rec*)SSL_get_app_data(inctx->filter_ctx->pssl);
+
+            if (ssl_err == SSL_ERROR_WANT_READ) {
+                /*
+                 * If OpenSSL wants to read more, and we were nonblocking,
+                 * report as an EAGAIN.  Otherwise loop, pulling more
+                 * data from network filter.
+                 *
+                 * (This is usually the case when the client forces an SSL
+                 * renegotation which is handled implicitly by OpenSSL.)
+                 */
+                inctx->rc = APR_EAGAIN;
+
+                if (*len > 0) {
+                    inctx->rc = APR_SUCCESS;
+                    break;
+                }
+                if (inctx->block == APR_NONBLOCK_READ) {
+                    break;
+                }
+                continue;  /* Blocking and nothing yet?  Try again. */
+            }
+            else if (ssl_err == SSL_ERROR_SYSCALL) {
+                if (APR_STATUS_IS_EAGAIN(inctx->rc)
+                        || APR_STATUS_IS_EINTR(inctx->rc)) {
+                    /* Already read something, return APR_SUCCESS instead. */
+                    if (*len > 0) {
+                        inctx->rc = APR_SUCCESS;
+                        break;
+                    }
+                    if (inctx->block == APR_NONBLOCK_READ) {
+                        break;
+                    }
+                    continue;  /* Blocking and nothing yet?  Try again. */
+                }
+                else {
+                    ap_log_error(APLOG_MARK, APLOG_INFO, inctx->rc, c->base_server,
+                                "SSL input filter read failed.");
+                }
+            }
+            else /* if (ssl_err == SSL_ERROR_SSL) */ {
+                /*
+                 * Log SSL errors and any unexpected conditions.
+                 */
+                ap_log_error(APLOG_MARK, APLOG_INFO, inctx->rc, c->base_server,
+                            "SSL library error %d reading data", ssl_err);
+                ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
+
+            }
+            if (inctx->rc == APR_SUCCESS) {
+                inctx->rc = APR_EGENERAL;
+            }
+            break;
+        }
+    }
+    return inctx->rc;
 }
 
-static apr_status_t ssl_io_input_getline(ssl_io_input_ctx_t *ctx,
+static apr_status_t ssl_io_input_getline(bio_filter_in_ctx_t *inctx,
                                          char *buf,
                                          apr_size_t *len)
 {
     const char *pos = NULL;
     apr_status_t status;
     apr_size_t tmplen = *len, buflen = *len, offset = 0;
