                 * we may finally destroy the request.
                 */
                (void)apr_thread_mutex_lock(cid->completed);
                break;
            }
            else if (cid->dconf.log_unsupported) {
                 ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02114)
                               "asynch I/O result HSE_STATUS_PENDING "
                               "from HttpExtensionProc() is not supported: %s",
                               r->filename);
                 r->status = HTTP_INTERNAL_SERVER_ERROR;
            }
            break;

        case HSE_STATUS_ERROR:
            /* end response if we have yet to do so.
             */
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, apr_get_os_error(), r, APLOGNO(02115)
                          "HSE_STATUS_ERROR result from "
                          "HttpExtensionProc(): %s", r->filename);
            r->status = HTTP_INTERNAL_SERVER_ERROR;
            break;

        default:
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, apr_get_os_error(), r, APLOGNO(02116)
                          "unrecognized result code %d "
                          "from HttpExtensionProc(): %s ",
                          rv, r->filename);
            r->status = HTTP_INTERNAL_SERVER_ERROR;
            break;
    }

    /* Flush the response now, including headers-only responses */
