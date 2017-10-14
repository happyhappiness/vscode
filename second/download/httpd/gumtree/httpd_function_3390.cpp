static apr_status_t isapi_handler (request_rec *r)
{
    isapi_dir_conf *dconf;
    apr_table_t *e;
    apr_status_t rv;
    isapi_loaded *isa;
    isapi_cid *cid;
    const char *val;
    apr_uint32_t read;
    int res;

    if(strcmp(r->handler, "isapi-isa")
        && strcmp(r->handler, "isapi-handler")) {
        /* Hang on to the isapi-isa for compatibility with older docs
         * (wtf did '-isa' mean in the first place?) but introduce
         * a newer and clearer "isapi-handler" name.
         */
        return DECLINED;
    }
    dconf = ap_get_module_config(r->per_dir_config, &isapi_module);
    e = r->subprocess_env;

    /* Use similar restrictions as CGIs
     *
     * If this fails, it's pointless to load the isapi dll.
     */
    if (!(ap_allow_options(r) & OPT_EXECCGI)) {
        return HTTP_FORBIDDEN;
    }
    if (r->finfo.filetype == APR_NOFILE) {
        return HTTP_NOT_FOUND;
    }
    if (r->finfo.filetype != APR_REG) {
        return HTTP_FORBIDDEN;
    }
    if ((r->used_path_info == AP_REQ_REJECT_PATH_INFO) &&
        r->path_info && *r->path_info) {
        /* default to accept */
        return HTTP_NOT_FOUND;
    }

    if (isapi_lookup(r->pool, r->server, r, r->filename, &isa)
           != APR_SUCCESS) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    /* Set up variables */
    ap_add_common_vars(r);
    ap_add_cgi_vars(r);
    apr_table_setn(e, "UNMAPPED_REMOTE_USER", "REMOTE_USER");
    if ((val = apr_table_get(e, "HTTPS")) && (strcmp(val, "on") == 0))
        apr_table_setn(e, "SERVER_PORT_SECURE", "1");
    else
        apr_table_setn(e, "SERVER_PORT_SECURE", "0");
    apr_table_setn(e, "URL", r->uri);

    /* Set up connection structure and ecb,
     * NULL or zero out most fields.
     */
    cid = apr_pcalloc(r->pool, sizeof(isapi_cid));

    /* Fixup defaults for dconf */
    cid->dconf.read_ahead_buflen = (dconf->read_ahead_buflen == ISAPI_UNDEF)
                                     ? 49152 : dconf->read_ahead_buflen;
    cid->dconf.log_unsupported   = (dconf->log_unsupported == ISAPI_UNDEF)
                                     ? 0 : dconf->log_unsupported;
    cid->dconf.log_to_errlog     = (dconf->log_to_errlog == ISAPI_UNDEF)
                                     ? 0 : dconf->log_to_errlog;
    cid->dconf.log_to_query      = (dconf->log_to_query == ISAPI_UNDEF)
                                     ? 1 : dconf->log_to_query;
    cid->dconf.fake_async        = (dconf->fake_async == ISAPI_UNDEF)
                                     ? 0 : dconf->fake_async;

    cid->ecb = apr_pcalloc(r->pool, sizeof(EXTENSION_CONTROL_BLOCK));
    cid->ecb->ConnID = cid;
    cid->isa = isa;
    cid->r = r;
    r->status = 0;

    cid->ecb->cbSize = sizeof(EXTENSION_CONTROL_BLOCK);
    cid->ecb->dwVersion = isa->report_version;
    cid->ecb->dwHttpStatusCode = 0;
    strcpy(cid->ecb->lpszLogData, "");
    /* TODO: are copies really needed here?
     */
    cid->ecb->lpszMethod = (char*) r->method;
    cid->ecb->lpszQueryString = (char*) apr_table_get(e, "QUERY_STRING");
    cid->ecb->lpszPathInfo = (char*) apr_table_get(e, "PATH_INFO");
    cid->ecb->lpszPathTranslated = (char*) apr_table_get(e, "PATH_TRANSLATED");
    cid->ecb->lpszContentType = (char*) apr_table_get(e, "CONTENT_TYPE");

    /* Set up the callbacks */
    cid->ecb->GetServerVariable = regfnGetServerVariable;
    cid->ecb->WriteClient = regfnWriteClient;
    cid->ecb->ReadClient = regfnReadClient;
    cid->ecb->ServerSupportFunction = regfnServerSupportFunction;

    /* Set up client input */
    res = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR);
    if (res) {
        return res;
    }

    if (ap_should_client_block(r)) {
        /* Time to start reading the appropriate amount of data,
         * and allow the administrator to tweak the number
         */
        if (r->remaining) {
            cid->ecb->cbTotalBytes = (apr_size_t)r->remaining;
            if (cid->ecb->cbTotalBytes > (apr_uint32_t)cid->dconf.read_ahead_buflen)
                cid->ecb->cbAvailable = cid->dconf.read_ahead_buflen;
            else
                cid->ecb->cbAvailable = cid->ecb->cbTotalBytes;
        }
        else
        {
            cid->ecb->cbTotalBytes = 0xffffffff;
            cid->ecb->cbAvailable = cid->dconf.read_ahead_buflen;
        }

        cid->ecb->lpbData = apr_pcalloc(r->pool, cid->ecb->cbAvailable + 1);

        read = 0;
        while (read < cid->ecb->cbAvailable &&
               ((res = ap_get_client_block(r, (char*)cid->ecb->lpbData + read,
                                        cid->ecb->cbAvailable - read)) > 0)) {
            read += res;
        }

        if (res < 0) {
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        /* Although it's not to spec, IIS seems to null-terminate
         * its lpdData string. So we will too.
         */
        if (res == 0)
            cid->ecb->cbAvailable = cid->ecb->cbTotalBytes = read;
        else
            cid->ecb->cbAvailable = read;
        cid->ecb->lpbData[read] = '\0';
    }
    else {
        cid->ecb->cbTotalBytes = 0;
        cid->ecb->cbAvailable = 0;
        cid->ecb->lpbData = NULL;
    }

    /* To emulate async behavior...
     *
     * We create a cid->completed mutex and lock on it so that the
     * app can believe is it running async.
     *
     * This request completes upon a notification through
     * ServerSupportFunction(HSE_REQ_DONE_WITH_SESSION), which
     * unlocks this mutex.  If the HttpExtensionProc() returns
     * HSE_STATUS_PENDING, we will attempt to gain this lock again
     * which may *only* happen once HSE_REQ_DONE_WITH_SESSION has
     * unlocked the mutex.
     */
    if (cid->dconf.fake_async) {
        rv = apr_thread_mutex_create(&cid->completed,
                                     APR_THREAD_MUTEX_UNNESTED,
                                     r->pool);
        if (cid->completed && (rv == APR_SUCCESS)) {
            rv = apr_thread_mutex_lock(cid->completed);
        }

        if (!cid->completed || (rv != APR_SUCCESS)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: Failed to create completion mutex");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    /* All right... try and run the sucker */
    rv = (*isa->HttpExtensionProc)(cid->ecb);

    /* Check for a log message - and log it */
    if (cid->ecb->lpszLogData && *cid->ecb->lpszLogData)
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                      "ISAPI: %s: %s", r->filename, cid->ecb->lpszLogData);

    switch(rv) {
        case 0:  /* Strange, but MS isapi accepts this as success */
        case HSE_STATUS_SUCCESS:
        case HSE_STATUS_SUCCESS_AND_KEEP_CONN:
            /* Ignore the keepalive stuff; Apache handles it just fine without
             * the ISAPI Handler's "advice".
             * Per Microsoft: "In IIS versions 4.0 and later, the return
             * values HSE_STATUS_SUCCESS and HSE_STATUS_SUCCESS_AND_KEEP_CONN
             * are functionally identical: Keep-Alive connections are
             * maintained, if supported by the client."
             * ... so we were pat all this time
             */
            break;

        case HSE_STATUS_PENDING:
            /* emulating async behavior...
             */
            if (cid->completed) {
                /* The completion port was locked prior to invoking
                 * HttpExtensionProc().  Once we can regain the lock,
                 * when ServerSupportFunction(HSE_REQ_DONE_WITH_SESSION)
                 * is called by the extension to release the lock,
                 * we may finally destroy the request.
                 */
                (void)apr_thread_mutex_lock(cid->completed);
                break;
            }
            else if (cid->dconf.log_unsupported) {
                 ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                               "ISAPI: asynch I/O result HSE_STATUS_PENDING "
                               "from HttpExtensionProc() is not supported: %s",
                               r->filename);
                 r->status = HTTP_INTERNAL_SERVER_ERROR;
            }
            break;

        case HSE_STATUS_ERROR:
            /* end response if we have yet to do so.
             */
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, apr_get_os_error(), r,
                          "ISAPI: HSE_STATUS_ERROR result from "
                          "HttpExtensionProc(): %s", r->filename);
            r->status = HTTP_INTERNAL_SERVER_ERROR;
            break;

        default:
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, apr_get_os_error(), r,
                          "ISAPI: unrecognized result code %d "
                          "from HttpExtensionProc(): %s ", 
                          rv, r->filename);
            r->status = HTTP_INTERNAL_SERVER_ERROR;
            break;
    }

    /* Flush the response now, including headers-only responses */
    if (cid->headers_set || cid->response_sent) {
        conn_rec *c = r->connection;
        apr_bucket_brigade *bb;
        apr_bucket *b;
        apr_status_t rv;

        bb = apr_brigade_create(r->pool, c->bucket_alloc);
        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        cid->response_sent = 1;

        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "ISAPI: ap_pass_brigade failed to "
                          "complete the response: %s ", r->filename);
        }

        return OK; /* NOT r->status, even if it has changed. */
    }

    /* As the client returned no error, and if we did not error out
     * ourselves, trust dwHttpStatusCode to say something relevant.
     */
    if (!ap_is_HTTP_SERVER_ERROR(r->status) && cid->ecb->dwHttpStatusCode) {
        r->status = cid->ecb->dwHttpStatusCode;
    }

    /* For all missing-response situations simply return the status,
     * and let the core respond to the client.
     */
    return r->status;
}