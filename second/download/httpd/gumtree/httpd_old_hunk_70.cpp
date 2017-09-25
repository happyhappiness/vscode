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
