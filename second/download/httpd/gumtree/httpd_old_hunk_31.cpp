        r->method_number = M_GET;

        /* Don't let anyone think there's still data */
        apr_table_unset(r->headers_in, "Content-Length");

        /* AV fault per PR3598 - redirected path is lost! */
        (char*)lpvBuffer = apr_pstrdup(r->pool, (char*)lpvBuffer);
        ap_internal_redirect((char*)lpvBuffer, r);
        return TRUE;

    case 3: /* HSE_REQ_SEND_RESPONSE_HEADER */
    {
        /* Parse them out, or die trying */
        apr_size_t statlen = 0, headlen = 0;
        apr_ssize_t ate;
        if (lpvBuffer)
            statlen = strlen((char*) lpvBuffer);
        if (lpdwDataType)
            headlen = strlen((char*) lpdwDataType);
        ate = SendResponseHeaderEx(cid, (char*) lpvBuffer,
                                   (char*) lpdwDataType,
                                   statlen, headlen);
        if (ate < 0) {
            SetLastError(TODO_ERROR);
            return FALSE;
        }
        else if ((apr_size_t)ate < headlen) {
            apr_bucket_brigade *bb;
            apr_bucket *b;
            bb = apr_brigade_create(cid->r->pool, c->bucket_alloc);
	    b = apr_bucket_transient_create((char*) lpdwDataType + ate, 
                                           headlen - ate, c->bucket_alloc);
	    APR_BRIGADE_INSERT_TAIL(bb, b);
            b = apr_bucket_flush_create(c->bucket_alloc);
	    APR_BRIGADE_INSERT_TAIL(bb, b);
	    ap_pass_brigade(cid->r->output_filters, bb);
        }
        return TRUE;
    }

    case 4: /* HSE_REQ_DONE_WITH_SESSION */
        /* Signal to resume the thread completing this request
         */
        if (cid->complete)
            SetEvent(cid->complete);            
        return TRUE;

    case 1001: /* HSE_REQ_MAP_URL_TO_PATH */
    {
        /* Map a URL to a filename */
        char *file = (char *)lpvBuffer;
        DWORD len;
        subreq = ap_sub_req_lookup_uri(apr_pstrndup(r->pool, file, *lpdwSize),
                                       r, NULL);

        len = apr_cpystrn(file, subreq->filename, *lpdwSize) - file;


        /* IIS puts a trailing slash on directories, Apache doesn't */
        if (subreq->finfo.filetype == APR_DIR) {
            if (len < *lpdwSize - 1) {
                file[len++] = '\\';
                file[len] = '\0';
            }
        }
        *lpdwSize = len;
        return TRUE;
    }

    case 1002: /* HSE_REQ_GET_SSPI_INFO */
        if (cid->sconf->LogNotSupported)
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                           "ISAPI ServerSupportFunction HSE_REQ_GET_SSPI_INFO "
                           "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
        
    case 1003: /* HSE_APPEND_LOG_PARAMETER */
        /* Log lpvBuffer, of lpdwSize bytes, in the URI Query (cs-uri-query) field
         */
        apr_table_set(r->notes, "isapi-parameter", (char*) lpvBuffer);
        if (cid->sconf->AppendLogToQuery) {
            if (r->args)
                r->args = apr_pstrcat(r->pool, r->args, (char*) lpvBuffer, NULL);
            else
                r->args = apr_pstrdup(r->pool, (char*) lpvBuffer);
        }
        if (cid->sconf->AppendLogToErrors)
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, r,
                          "ISAPI %s: %s", cid->r->filename,
                          (char*) lpvBuffer);
        return TRUE;
        
    case 1005: /* HSE_REQ_IO_COMPLETION */
        /* Emulates a completion port...  Record callback address and 
         * user defined arg, we will call this after any async request 
         * (e.g. transmitfile) as if the request executed async.
         * Per MS docs... HSE_REQ_IO_COMPLETION replaces any prior call
         * to HSE_REQ_IO_COMPLETION, and lpvBuffer may be set to NULL.
         */
        if (!cid->isa->fakeasync) {
            if (cid->sconf->LogNotSupported)
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI ServerSupportFunction HSE_REQ_IO_COMPLETION "
                          "is not supported: %s", r->filename);
            SetLastError(ERROR_INVALID_PARAMETER);
            return FALSE;
        }
        cid->completion = (PFN_HSE_IO_COMPLETION) lpvBuffer;
        cid->completion_arg = (PVOID) lpdwDataType;
        return TRUE;

    case 1006: /* HSE_REQ_TRANSMIT_FILE */
    {
        HSE_TF_INFO *tf = (HSE_TF_INFO*)lpvBuffer;
        apr_status_t rv;
        apr_bucket_brigade *bb;
        apr_bucket *b;
        apr_file_t *fd;

        if (!cid->isa->fakeasync && (tf->dwFlags & HSE_IO_ASYNC)) {
            if (cid->sconf->LogNotSupported)
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                         "ISAPI ServerSupportFunction HSE_REQ_TRANSMIT_FILE "
                         "as HSE_IO_ASYNC is not supported: %s", r->filename);
            SetLastError(ERROR_INVALID_PARAMETER);
            return FALSE;
        }
        
        if ((rv = apr_os_file_put(&fd, tf->hFile, 0, r->pool)) != APR_SUCCESS) {
            return FALSE;
        }
        
        /* apr_dupfile_oshandle (&fd, tf->hFile, r->pool); */
        bb = apr_brigade_create(r->pool, c->bucket_alloc);

        if (tf->dwFlags & HSE_IO_SEND_HEADERS) 
        {
            /* According to MS: if calling HSE_REQ_TRANSMIT_FILE with the
             * HSE_IO_SEND_HEADERS flag, then you can't otherwise call any
             * HSE_SEND_RESPONSE_HEADERS* fn, but if you don't use the flag,
             * you must have done so.  They document that the pHead headers
             * option is valid only for HSE_IO_SEND_HEADERS - we are a bit
             * more flexible and assume with the flag, pHead are the
             * response headers, and without, pHead simply contains text
             * (handled after this case).
             */
            apr_ssize_t ate = SendResponseHeaderEx(cid, tf->pszStatusCode, 
                                                   (char*)tf->pHead,
                                                   strlen(tf->pszStatusCode), 
                                                   tf->HeadLength);
            if (ate < 0)
            {
                apr_brigade_destroy(bb);
                SetLastError(TODO_ERROR);
                return FALSE;
            }
            if ((apr_size_t)ate < tf->HeadLength)
            {
                b = apr_bucket_transient_create((char*)tf->pHead + ate, 
                                                tf->HeadLength - ate,
                                                c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, b);
            }
        }
        else if (tf->pHead && tf->HeadLength) {
            b = apr_bucket_transient_create((char*)tf->pHead, 
                                            tf->HeadLength,
                                            c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
        }

        b = apr_bucket_file_create(fd, tf->Offset, 
                                   tf->BytesToWrite, r->pool, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        
        if (tf->pTail && tf->TailLength) {
            b = apr_bucket_transient_create((char*)tf->pTail, 
                                            tf->TailLength, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
        }
        
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        ap_pass_brigade(r->output_filters, bb);

        /* we do nothing with (tf->dwFlags & HSE_DISCONNECT_AFTER_SEND)
         */

        if (tf->dwFlags & HSE_IO_ASYNC) {
            /* XXX: Fake async response,
             * use tf->pfnHseIO, or if NULL, then use cid->fnIOComplete
             * pass pContect to the HseIO callback.
             */
        }
        return TRUE;
    }

    case 1007: /* HSE_REQ_REFRESH_ISAPI_ACL */
        if (cid->sconf->LogNotSupported)
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI ServerSupportFunction "
                          "HSE_REQ_REFRESH_ISAPI_ACL "
                          "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;

    case 1008: /* HSE_REQ_IS_KEEP_CONN */
        *((LPBOOL) lpvBuffer) = (r->connection->keepalive == 1);
        return TRUE;

    case 1010: /* XXX: Fake it : HSE_REQ_ASYNC_READ_CLIENT */
        if (cid->sconf->LogNotSupported)
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI asynchronous I/O not supported: %s", 
                          r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;

    case 1011: /* HSE_REQ_GET_IMPERSONATION_TOKEN  Added in ISAPI 4.0 */
        if (cid->sconf->LogNotSupported)
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI ServerSupportFunction "
                          "HSE_REQ_GET_IMPERSONATION_TOKEN "
                          "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;

#ifdef HSE_REQ_MAP_URL_TO_PATH_EX
    case 1012: /* HSE_REQ_MAP_URL_TO_PATH_EX */
    {
        /* Map a URL to a filename */
        LPHSE_URL_MAPEX_INFO info = (LPHSE_URL_MAPEX_INFO) lpdwDataType;
        char* test_uri = apr_pstrndup(r->pool, (char *)lpvBuffer, *lpdwSize);

        subreq = ap_sub_req_lookup_uri(test_uri, r, NULL);
        info->cchMatchingURL = strlen(test_uri);        
        info->cchMatchingPath = apr_cpystrn(info->lpszPath, subreq->filename, 
                                            MAX_PATH) - info->lpszPath;

        /* Mapping started with assuming both strings matched.
         * Now roll on the path_info as a mismatch and handle
         * terminating slashes for directory matches.
         */
        if (subreq->path_info && *subreq->path_info) {
