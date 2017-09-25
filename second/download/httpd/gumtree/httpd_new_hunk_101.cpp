
      default:
        return status;
    }

    APR_BRIGADE_INSERT_TAIL(bb, bucket);
    bucket = apr_bucket_eos_create(f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, bucket);

    return APR_SUCCESS;
}

static const char ssl_io_filter[] = "SSL/TLS Filter";

/*
 *  Close the SSL part of the socket connection
 *  (called immediately _before_ the socket is closed)
 *  or called with 
 */
static apr_status_t ssl_filter_io_shutdown(ssl_filter_ctx_t *filter_ctx,
                                           conn_rec *c,
                                           int abortive)
{
    SSL *ssl = filter_ctx->pssl;
    const char *type = "";
    SSLConnRec *sslconn = myConnConfig(c);
    int shutdown_type;

    if (!ssl) {
        return APR_SUCCESS;
    }

    /*
     * Now close the SSL layer of the connection. We've to take
     * the TLSv1 standard into account here:
     *
     * | 7.2.1. Closure alerts
     * |
     * | The client and the server must share knowledge that the connection is
     * | ending in order to avoid a truncation attack. Either party may
     * | initiate the exchange of closing messages.
     * |
     * | close_notify
     * |     This message notifies the recipient that the sender will not send
     * |     any more messages on this connection. The session becomes
     * |     unresumable if any connection is terminated without proper
     * |     close_notify messages with level equal to warning.
     * |
     * | Either party may initiate a close by sending a close_notify alert.
     * | Any data received after a closure alert is ignored.
     * |
     * | Each party is required to send a close_notify alert before closing
     * | the write side of the connection. It is required that the other party
     * | respond with a close_notify alert of its own and close down the
     * | connection immediately, discarding any pending writes. It is not
     * | required for the initiator of the close to wait for the responding
     * | close_notify alert before closing the read side of the connection.
     *
     * This means we've to send a close notify message, but haven't to wait
     * for the close notify of the client. Actually we cannot wait for the
     * close notify of the client because some clients (including Netscape
     * 4.x) don't send one, so we would hang.
     */

    /*
     * exchange close notify messages, but allow the user
     * to force the type of handshake via SetEnvIf directive
     */
    if (abortive) {
        shutdown_type = SSL_SENT_SHUTDOWN|SSL_RECEIVED_SHUTDOWN;
        type = "abortive";
    }
    else switch (sslconn->shutdown_type) {
      case SSL_SHUTDOWN_TYPE_UNCLEAN:
        /* perform no close notify handshake at all
           (violates the SSL/TLS standard!) */
        shutdown_type = SSL_SENT_SHUTDOWN|SSL_RECEIVED_SHUTDOWN;
        type = "unclean";
        break;
      case SSL_SHUTDOWN_TYPE_ACCURATE:
        /* send close notify and wait for clients close notify
           (standard compliant, but usually causes connection hangs) */
        shutdown_type = 0;
        type = "accurate";
        break;
      default:
        /*
         * case SSL_SHUTDOWN_TYPE_UNSET:
         * case SSL_SHUTDOWN_TYPE_STANDARD:
         */
        /* send close notify, but don't wait for clients close notify
           (standard compliant and safe, so it's the DEFAULT!) */
        shutdown_type = SSL_RECEIVED_SHUTDOWN;
        type = "standard";
        break;
    }

    SSL_set_shutdown(ssl, shutdown_type);
    SSL_smart_shutdown(ssl);

    /* and finally log the fact that we've closed the connection */
    if (c->base_server->loglevel >= APLOG_INFO) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, c->base_server,
                     "Connection to child %ld closed with %s shutdown"
                     "(server %s, client %s)",
                     c->id, type,
                     ssl_util_vhostid(c->pool, c->base_server),
                     c->remote_ip ? c->remote_ip : "unknown");
    }

    /* deallocate the SSL connection */
    SSL_free(ssl);
    sslconn->ssl = NULL;
    filter_ctx->pssl = NULL; /* so filters know we've been shutdown */

    return APR_SUCCESS;
}

static apr_status_t ssl_io_filter_cleanup(void *data)
{
    apr_status_t ret;
    ssl_filter_ctx_t *filter_ctx = (ssl_filter_ctx_t *)data;
    conn_rec *c;

    if (!filter_ctx->pssl) {
        /* already been shutdown */
        return APR_SUCCESS;
    }

    c = (conn_rec *)SSL_get_app_data(filter_ctx->pssl);
    if ((ret = ssl_filter_io_shutdown(filter_ctx, c, 0)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_INFO, ret, NULL,
                     "SSL filter error shutting down I/O");
    }

    return ret;
}

/*
 * The hook is NOT registered with ap_hook_process_connection. Instead, it is
 * called manually from the churn () before it tries to read any data.
 * There is some problem if I accept conn_rec *. Still investigating..
 * Adv. if conn_rec * can be accepted is we can hook this function using the
 * ap_hook_process_connection hook.
 */
static int ssl_io_filter_connect(ssl_filter_ctx_t *filter_ctx)
{
    conn_rec *c         = (conn_rec *)SSL_get_app_data(filter_ctx->pssl);
    SSLConnRec *sslconn = myConnConfig(c);
    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
    X509 *cert;
    int n;
    int ssl_err;
    long verify_result;

    if (SSL_is_init_finished(filter_ctx->pssl)) {
        return APR_SUCCESS;
    }

    if (sslconn->is_proxy) {
        if ((n = SSL_connect(filter_ctx->pssl)) <= 0) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         c->base_server,
                         "SSL Proxy connect failed");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
            return ssl_filter_io_shutdown(filter_ctx, c, 1);
        }

        return APR_SUCCESS;
    }

    if ((n = SSL_accept(filter_ctx->pssl)) <= 0) {
        bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)
                                     (filter_ctx->pbioRead->ptr);
        bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)
                                       (filter_ctx->pbioWrite->ptr);
        apr_status_t rc = inctx->rc ? inctx->rc : outctx->rc ;
        ssl_err = SSL_get_error(filter_ctx->pssl, n);
        
        if (ssl_err == SSL_ERROR_ZERO_RETURN) {
            /*
             * The case where the connection was closed before any data
             * was transferred. That's not a real error and can occur
             * sporadically with some clients.
             */
            ap_log_error(APLOG_MARK, APLOG_INFO, rc,
                         c->base_server,
                         "SSL handshake stopped: connection was closed");
        }
        else if (ssl_err == SSL_ERROR_WANT_READ) {
            /*
             * This is in addition to what was present earlier. It is 
             * borrowed from openssl_state_machine.c [mod_tls].
             * TBD.
             */
            outctx->rc = APR_EAGAIN;
            return SSL_ERROR_WANT_READ;
        }
        else if (ERR_GET_REASON(ERR_peek_error()) == SSL_R_HTTP_REQUEST) {
            /*
             * The case where OpenSSL has recognized a HTTP request:
             * This means the client speaks plain HTTP on our HTTPS port.
             * ssl_io_filter_error will disable the ssl filters when it
             * sees this status code.
             */
            return HTTP_BAD_REQUEST;
        }
        else if (ssl_err == SSL_ERROR_SYSCALL) {
            ap_log_error(APLOG_MARK, APLOG_INFO, rc, c->base_server,
                         "SSL handshake interrupted by system "
                         "[Hint: Stop button pressed in browser?!]");
        }
        else /* if (ssl_err == SSL_ERROR_SSL) */ {
            /*
             * Log SSL errors and any unexpected conditions.
             */
            ap_log_error(APLOG_MARK, APLOG_INFO, rc, c->base_server,
                         "SSL library error %d in handshake "
                         "(server %s, client %s)", ssl_err,
                         ssl_util_vhostid(c->pool, c->base_server),
                         c->remote_ip ? c->remote_ip : "unknown");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);

        }
        if (inctx->rc == APR_SUCCESS) {
            inctx->rc = APR_EGENERAL;
        }

        return ssl_filter_io_shutdown(filter_ctx, c, 1);
    }

    /*
     * Check for failed client authentication
     */
    verify_result = SSL_get_verify_result(filter_ctx->pssl);

    if ((verify_result != X509_V_OK) ||
        sslconn->verify_error)
    {
        if (ssl_verify_error_is_optional(verify_result) &&
            (sc->server->auth.verify_mode == SSL_CVERIFY_OPTIONAL_NO_CA))
        {
            /* leaving this log message as an error for the moment,
             * according to the mod_ssl docs:
             * "level optional_no_ca is actually against the idea
             *  of authentication (but can be used to establish 
             * SSL test pages, etc.)"
             * optional_no_ca doesn't appear to work as advertised
             * in 1.x
             */
            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         c->base_server,
                         "SSL client authentication failed, "
                         "accepting certificate based on "
                         "\"SSLVerifyClient optional_no_ca\" "
                         "configuration");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
        }
        else {
            const char *error = sslconn->verify_error ?
                sslconn->verify_error :
                X509_verify_cert_error_string(verify_result);

            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         c->base_server,
                         "SSL client authentication failed: %s",
                         error ? error : "unknown");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);

            return ssl_filter_io_shutdown(filter_ctx, c, 1);
        }
    }

    /*
     * Remember the peer certificate's DN
     */
    if ((cert = SSL_get_peer_certificate(filter_ctx->pssl))) {
        sslconn->client_cert = cert;
        sslconn->client_dn = NULL;
        X509_free(cert);
    }

    /*
     * Make really sure that when a peer certificate
     * is required we really got one... (be paranoid)
     */
    if ((sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE) &&
        !sslconn->client_cert)
    {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, c->base_server,
                     "No acceptable peer certificate available");

        return ssl_filter_io_shutdown(filter_ctx, c, 1);
    }

    return APR_SUCCESS;
}

static apr_status_t ssl_io_filter_input(ap_filter_t *f,
                                        apr_bucket_brigade *bb,
                                        ap_input_mode_t mode,
                                        apr_read_type_e block,
                                        apr_off_t readbytes)
{
    apr_status_t status;
    bio_filter_in_ctx_t *inctx = f->ctx;

    apr_size_t len = sizeof(inctx->buffer);
    int is_init = (mode == AP_MODE_INIT);

    if (f->c->aborted) {
        /* XXX: Ok, if we aborted, we ARE at the EOS.  We also have
         * aborted.  This 'double protection' is probably redundant,
         * but also effective against just about anything.
         */
        apr_bucket *bucket = apr_bucket_eos_create(f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, bucket);
        return APR_ECONNABORTED;
    }

    if (!inctx->ssl) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    /* XXX: we don't currently support anything other than these modes. */
    if (mode != AP_MODE_READBYTES && mode != AP_MODE_GETLINE && 
        mode != AP_MODE_SPECULATIVE && mode != AP_MODE_INIT) {
        return APR_ENOTIMPL;
    }

    inctx->mode = mode;
    inctx->block = block;

    /* XXX: we could actually move ssl_io_filter_connect to an
     * ap_hook_process_connection but would still need to call it for
     * AP_MODE_INIT for protocols that may upgrade the connection
     * rather than have SSLEngine On configured.
     */
    if ((status = ssl_io_filter_connect(inctx->filter_ctx)) != APR_SUCCESS) {
        return ssl_io_filter_error(f, bb, status);
    }

    if (is_init) {
        /* protocol module needs to handshake before sending
         * data to client (e.g. NNTP or FTP)
         */
        return APR_SUCCESS;
    }

    if (inctx->mode == AP_MODE_READBYTES || 
        inctx->mode == AP_MODE_SPECULATIVE) {
        /* Protected from truncation, readbytes < MAX_SIZE_T 
         * FIXME: No, it's *not* protected.  -- jre */
        if (readbytes < len) {
            len = (apr_size_t)readbytes;
        }
        status = ssl_io_input_read(inctx, inctx->buffer, &len);
    }
    else if (inctx->mode == AP_MODE_GETLINE) {
        status = ssl_io_input_getline(inctx, inctx->buffer, &len);
    }
    else {
        /* We have no idea what you are talking about, so return an error. */
        return APR_ENOTIMPL;
    }

    if (status != APR_SUCCESS) {
        return ssl_io_filter_error(f, bb, status);
    }

    /* Create a transient bucket out of the decrypted data. */
    if (len > 0) {
        apr_bucket *bucket =
            apr_bucket_transient_create(inctx->buffer, len, f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, bucket);
    }

    return APR_SUCCESS;
}

static apr_status_t ssl_io_filter_output(ap_filter_t *f,
                                         apr_bucket_brigade *bb)
{
    apr_status_t status = APR_SUCCESS;
    ssl_filter_ctx_t *filter_ctx = f->ctx;

    if (f->c->aborted) {
        apr_brigade_cleanup(bb);
        return APR_ECONNABORTED;
    }

    if (!filter_ctx->pssl) {
        /* ssl_filter_io_shutdown was called */
        return ap_pass_brigade(f->next, bb);
    }

    if ((status = ssl_io_filter_connect(filter_ctx)) != APR_SUCCESS) {
        return ssl_io_filter_error(f, bb, status);
    }

    while (!APR_BRIGADE_EMPTY(bb)) {
        apr_bucket *bucket = APR_BRIGADE_FIRST(bb);

        /* If it is a flush or EOS, we need to pass this down. 
         * These types do not require translation by OpenSSL.  
         */
        if (APR_BUCKET_IS_EOS(bucket) || APR_BUCKET_IS_FLUSH(bucket)) {
            if (bio_filter_out_flush(filter_ctx->pbioWrite) < 0) {
                bio_filter_out_ctx_t *outctx = 
                       (bio_filter_out_ctx_t *)(filter_ctx->pbioWrite->ptr);
                status = outctx->rc;
                break;
            }

            if (APR_BUCKET_IS_EOS(bucket)) {
                /*
                 * By definition, nothing can come after EOS.
                 * which also means we can pass the rest of this brigade
                 * without creating a new one since it only contains the
                 * EOS bucket.
                 */

                if ((status = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
                    return status;
                }
                break;
            }
            else {
                /* bio_filter_out_flush() already passed down a flush bucket
                 * if there was any data to be flushed.
                 */
                apr_bucket_delete(bucket);
            }
        }
        else {
            /* filter output */
            const char *data;
            apr_size_t len;
            
            status = apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);

            if (!APR_STATUS_IS_EOF(status) && (status != APR_SUCCESS)) {
                break;
            }

            status = ssl_filter_write(f, data, len);
            apr_bucket_delete(bucket);

            if (status != APR_SUCCESS) {
                break;
            }
        }
    }

    return status;
}

static void ssl_io_input_add_filter(ssl_filter_ctx_t *filter_ctx, conn_rec *c,
                                    SSL *ssl)
{
    bio_filter_in_ctx_t *inctx;

    inctx = apr_palloc(c->pool, sizeof(*inctx));

    filter_ctx->pInputFilter = ap_add_input_filter(ssl_io_filter, inctx, NULL, c);

    filter_ctx->pbioRead = BIO_new(&bio_filter_in_method);
    filter_ctx->pbioRead->ptr = (void *)inctx;

    inctx->filter_ctx = filter_ctx;
    inctx->ssl = ssl;
    inctx->bio_out = filter_ctx->pbioWrite;
    inctx->f = filter_ctx->pInputFilter;
    inctx->bb = apr_brigade_create(c->pool, c->bucket_alloc);

    inctx->cbuf.length = 0;

    inctx->pool = c->pool;
}

void ssl_io_filter_init(conn_rec *c, SSL *ssl)
{
    ssl_filter_ctx_t *filter_ctx;

    filter_ctx = apr_palloc(c->pool, sizeof(ssl_filter_ctx_t));

    filter_ctx->pOutputFilter   = ap_add_output_filter(ssl_io_filter,
                                                   filter_ctx, NULL, c);

    filter_ctx->pbioWrite       = BIO_new(&bio_filter_out_method);
    filter_ctx->pbioWrite->ptr  = (void *)bio_filter_out_ctx_new(filter_ctx, c);

    ssl_io_input_add_filter(filter_ctx, c, ssl);

    SSL_set_bio(ssl, filter_ctx->pbioRead, filter_ctx->pbioWrite);
    filter_ctx->pssl            = ssl;

    apr_pool_cleanup_register(c->pool, (void*)filter_ctx,
                              ssl_io_filter_cleanup, apr_pool_cleanup_null);

    if (c->base_server->loglevel >= APLOG_DEBUG) {
        BIO_set_callback(SSL_get_rbio(ssl), ssl_io_data_cb);
        BIO_set_callback_arg(SSL_get_rbio(ssl), (void *)ssl);
    }

    return;
}

void ssl_io_filter_register(apr_pool_t *p)
{
    ap_register_input_filter  (ssl_io_filter, ssl_io_filter_input,  NULL, AP_FTYPE_CONNECTION + 5);
    ap_register_output_filter (ssl_io_filter, ssl_io_filter_output, NULL, AP_FTYPE_CONNECTION + 5);
    return;
}

/*  _________________________________________________________________
**
**  I/O Data Debugging
