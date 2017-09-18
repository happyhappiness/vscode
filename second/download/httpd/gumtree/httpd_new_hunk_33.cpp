                                            c->bucket_alloc);
	    APR_BRIGADE_INSERT_TAIL(bb, b);
            b = apr_bucket_flush_create(c->bucket_alloc);
	    APR_BRIGADE_INSERT_TAIL(bb, b);
	    ap_pass_brigade(cid->r->output_filters, bb);
        }
        return 1;
    }

    case HSE_REQ_CLOSE_CONNECTION:  /* Added after ISAPI 4.0 */
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction "
                          "HSE_REQ_CLOSE_CONNECTION "
                          "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;

    case HSE_REQ_IS_CONNECTED:  /* Added after ISAPI 4.0 */
        /* Returns True if client is connected c.f. MSKB Q188346
         * assuming the identical return mechanism as HSE_REQ_IS_KEEP_CONN
         */
        *((int *)buf_data) = (r->connection->aborted == 0);
        return 1;

    case HSE_REQ_EXTENSION_TRIGGER:  /* Added after ISAPI 4.0 */
        /*  Undocumented - defined by the Microsoft Jan '00 Platform SDK
         */
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction "
                          "HSE_REQ_EXTENSION_TRIGGER "
                          "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;

    default:
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction (%d) not supported: "
                          "%s", HSE_code, r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;
    }
}

/**********************************************************
 *
 *  ISAPI Module request invocation section
 *
 **********************************************************/

apr_status_t isapi_handler (request_rec *r)
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
    if ((val = apr_table_get(e, "HTTPS")) && strcmp(val, "on"))
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
                                     ? 48192 : dconf->read_ahead_buflen;
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
    cid->r->status = 0;
    
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
    
    /* Based on some examples I've noticed, NULL is expected here. 
     */
    if (!*cid->ecb->lpszQueryString) {
        cid->ecb->lpszQueryString = NULL;
    }

    /* Set up the callbacks */
    cid->ecb->GetServerVariable = GetServerVariable;
    cid->ecb->WriteClient = WriteClient;
    cid->ecb->ReadClient = ReadClient;
    cid->ecb->ServerSupportFunction = ServerSupportFunction;

    /* Set up client input */
    res = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR);
    if (res) {
        isapi_unload(isa, 0);
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
               ((res = ap_get_client_block(r, cid->ecb->lpbData + read,
                                        cid->ecb->cbAvailable - read)) > 0)) {
            read += res;
        }

        if (res < 0) {
            isapi_unload(isa, 0);
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
             *
             * Create a cid->completed mutex and wait on it for some timeout
             * so that the app thinks is it running async.
             *
             * All async ServerSupportFunction calls will be handled through
             * the registered IO_COMPLETION hook.
             *
             * This request completes upon a notification through
             * ServerSupportFunction(HSE_REQ_DONE_WITH_SESSION)
             */
            if (cid->dconf.fake_async) {
                apr_thread_mutex_t *comp;

                rv = apr_thread_mutex_create(&cid->completed, 
                                             APR_THREAD_MUTEX_UNNESTED, 
                                             r->pool);
                comp = cid->completed;
                if (cid->completed && (rv == APR_SUCCESS)) {
                    rv = apr_thread_mutex_lock(comp);
                }
                /* The completion port is now locked.  When we regain the
                 * lock, we may destroy the request.
                 */
                if (cid->completed && (rv == APR_SUCCESS)) {
                    rv = apr_thread_mutex_lock(comp);
                }
                break;
            }
            else if (cid->dconf.log_unsupported) {
                 ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                               "ISAPI: asynch I/O result HSE_STATUS_PENDING "
                               "from HttpExtensionProc() is not supported: %s",
                               r->filename);
                 cid->r->status = HTTP_INTERNAL_SERVER_ERROR;
            }
            break;

        case HSE_STATUS_ERROR:    
            /* end response if we have yet to do so.
             */
            cid->r->status = HTTP_INTERNAL_SERVER_ERROR;
            break;

        default:
            /* TODO: log unrecognized retval for debugging 
             */
            cid->r->status = HTTP_INTERNAL_SERVER_ERROR;
            break;
    }

    /* Set the status (for logging) */
    if (cid->ecb->dwHttpStatusCode) {
        cid->r->status = cid->ecb->dwHttpStatusCode;
    }

    return cid->r->status;
}

/**********************************************************
 *
 *  ISAPI Module Setup Hooks
 *
 **********************************************************/

static int isapi_pre_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
{
    apr_status_t rv;

    apr_pool_sub_make(&loaded.pool, pconf, NULL);
    if (!loaded.pool) {
	ap_log_error(APLOG_MARK, APLOG_ERR, APR_EGENERAL, NULL,
	             "ISAPI: could not create the isapi cache pool");
        return APR_EGENERAL;
    }
    
    loaded.hash = apr_hash_make(loaded.pool);
    if (!loaded.hash) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "ISAPI: Failed to create module cache");
        return APR_EGENERAL;
    }

    rv = apr_thread_mutex_create(&loaded.lock, APR_THREAD_MUTEX_DEFAULT, 
                                 loaded.pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, rv, 0, NULL,
                     "ISAPI: Failed to create module cache lock");
        return rv;
    }
    return OK;
}

static void isapi_hooks(apr_pool_t *cont)
{
    ap_hook_pre_config(isapi_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(isapi_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA isapi_module = {
   STANDARD20_MODULE_STUFF,
   create_isapi_dir_config,     /* create per-dir config */
   merge_isapi_dir_configs,     /* merge per-dir config */
   NULL,                        /* server config */
   NULL,                        /* merge server config */
   isapi_cmds,                  /* command apr_table_t */
   isapi_hooks                  /* register hooks */
};
