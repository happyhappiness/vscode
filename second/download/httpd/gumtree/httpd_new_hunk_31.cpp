        r->method_number = M_GET;

        /* Don't let anyone think there's still data */
        apr_table_unset(r->headers_in, "Content-Length");

        /* AV fault per PR3598 - redirected path is lost! */
        (char*)buf_data = apr_pstrdup(r->pool, (char*)buf_data);
        ap_internal_redirect((char*)buf_data, r);
        return 1;

    case HSE_REQ_SEND_RESPONSE_HEADER:
    {
        /* Parse them out, or die trying */
        apr_size_t statlen = 0, headlen = 0;
        apr_ssize_t ate;
        if (buf_data)
            statlen = strlen((char*) buf_data);
        if (data_type)
            headlen = strlen((char*) data_type);
        ate = send_response_header(cid, (char*) buf_data,
                                   (char*) data_type,
                                   statlen, headlen);
        if (ate < 0) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return 0;
        }
        else if ((apr_size_t)ate < headlen) {
            apr_bucket_brigade *bb;
            apr_bucket *b;
            bb = apr_brigade_create(cid->r->pool, c->bucket_alloc);
	    b = apr_bucket_transient_create((char*) data_type + ate, 
                                           headlen - ate, c->bucket_alloc);
	    APR_BRIGADE_INSERT_TAIL(bb, b);
            b = apr_bucket_flush_create(c->bucket_alloc);
	    APR_BRIGADE_INSERT_TAIL(bb, b);
	    ap_pass_brigade(cid->r->output_filters, bb);
        }
        return 1;
    }

    case HSE_REQ_DONE_WITH_SESSION:
        /* Signal to resume the thread completing this request,
         * leave it to the pool cleanup to dispose of our mutex.
         */
        if (cid->completed) {
            apr_thread_mutex_unlock(cid->completed);
        }
        return 1;

    case HSE_REQ_MAP_URL_TO_PATH:
    {
        /* Map a URL to a filename */
        char *file = (char *)buf_data;
        apr_uint32_t len;
        subreq = ap_sub_req_lookup_uri(apr_pstrndup(r->pool, file, *buf_size),
                                       r, NULL);

        len = apr_cpystrn(file, subreq->filename, *buf_size) - file;


        /* IIS puts a trailing slash on directories, Apache doesn't */
        if (subreq->finfo.filetype == APR_DIR) {
            if (len < *buf_size - 1) {
                file[len++] = '\\';
                file[len] = '\0';
            }
        }
        *buf_size = len;
        return 1;
    }

    case HSE_REQ_GET_SSPI_INFO:
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                           "ISAPI: ServerSupportFunction HSE_REQ_GET_SSPI_INFO "
                           "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;
        
    case HSE_APPEND_LOG_PARAMETER:
        /* Log buf_data, of buf_size bytes, in the URI Query (cs-uri-query) field
         */
        apr_table_set(r->notes, "isapi-parameter", (char*) buf_data);
        if (cid->dconf.log_to_query) {
            if (r->args)
                r->args = apr_pstrcat(r->pool, r->args, (char*) buf_data, NULL);
            else
                r->args = apr_pstrdup(r->pool, (char*) buf_data);
        }
        if (cid->dconf.log_to_errlog)
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "ISAPI: %s: %s", cid->r->filename,
                          (char*) buf_data);
        return 1;
        
    case HSE_REQ_IO_COMPLETION:
        /* Emulates a completion port...  Record callback address and 
         * user defined arg, we will call this after any async request 
         * (e.g. transmitfile) as if the request executed async.
         * Per MS docs... HSE_REQ_IO_COMPLETION replaces any prior call
         * to HSE_REQ_IO_COMPLETION, and buf_data may be set to NULL.
         */
        if (cid->dconf.fake_async) {
            cid->completion = (PFN_HSE_IO_COMPLETION) buf_data;
            cid->completion_arg = (void *) data_type;
            return 1;
        }
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                      "ISAPI: ServerSupportFunction HSE_REQ_IO_COMPLETION "
                      "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;

    case HSE_REQ_TRANSMIT_FILE:
    {
        /* we do nothing with (tf->dwFlags & HSE_DISCONNECT_AFTER_SEND)
         */
        HSE_TF_INFO *tf = (HSE_TF_INFO*)buf_data;
        apr_uint32_t sent = 0;
        apr_ssize_t ate = 0;
        apr_status_t rv;
        apr_bucket_brigade *bb;
        apr_bucket *b;
        apr_file_t *fd;
        apr_off_t fsize;

        if (!cid->dconf.fake_async && (tf->dwFlags & HSE_IO_ASYNC)) {
            if (cid->dconf.log_unsupported)
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                         "ISAPI: ServerSupportFunction HSE_REQ_TRANSMIT_FILE "
                         "as HSE_IO_ASYNC is not supported: %s", r->filename);
            SetLastError(ERROR_INVALID_PARAMETER);
            return 0;
        }
        
        /* Presume the handle was opened with the CORRECT semantics
         * for TransmitFile 
         */
        if ((rv = apr_os_file_put(&fd, &tf->hFile, 
                                  APR_READ | APR_XTHREAD, r->pool)) 
                != APR_SUCCESS) {
            return 0;
        }
        if (tf->BytesToWrite) {
            fsize = tf->BytesToWrite;
        }
        else {
            apr_finfo_t fi;
            if (apr_file_info_get(&fi, APR_FINFO_SIZE, fd) != APR_SUCCESS) {
                SetLastError(ERROR_INVALID_PARAMETER);
                return 0;
            }
            fsize = fi.size - tf->Offset;
        }
        
        /* apr_dupfile_oshandle (&fd, tf->hFile, r->pool); */
        bb = apr_brigade_create(r->pool, c->bucket_alloc);

        /* According to MS: if calling HSE_REQ_TRANSMIT_FILE with the
         * HSE_IO_SEND_HEADERS flag, then you can't otherwise call any
         * HSE_SEND_RESPONSE_HEADERS* fn, but if you don't use the flag,
         * you must have done so.  They document that the pHead headers
         * option is valid only for HSE_IO_SEND_HEADERS - we are a bit
         * more flexible and assume with the flag, pHead are the
         * response headers, and without, pHead simply contains text
         * (handled after this case).
         */
        if ((tf->dwFlags & HSE_IO_SEND_HEADERS) && tf->pszStatusCode) {
            ate = send_response_header(cid, tf->pszStatusCode,  
                                            (char*)tf->pHead,
                                            strlen(tf->pszStatusCode),
                                            tf->HeadLength);
        }
        else if (!cid->headers_sent && tf->pHead && tf->HeadLength 
                                    && *(char*)tf->pHead) {
            ate = send_response_header(cid, NULL, (char*)tf->pHead,
                                            0, tf->HeadLength);
            if (ate < 0)
            {
                apr_brigade_destroy(bb);
                SetLastError(ERROR_INVALID_PARAMETER);
                return 0;
            }
        }

        if (tf->pHead && (apr_size_t)ate < tf->HeadLength) {
            sent = tf->HeadLength - ate;
            b = apr_bucket_transient_create((char*)tf->pHead + ate, 
                                            sent, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
        }

        sent += (apr_uint32_t)fsize;
#if APR_HAS_LARGE_FILES
        if (r->finfo.size > AP_MAX_SENDFILE) {
            /* APR_HAS_LARGE_FILES issue; must split into mutiple buckets,
             * no greater than MAX(apr_size_t), and more granular than that
             * in case the brigade code/filters attempt to read it directly.
             */
            b = apr_bucket_file_create(fd, tf->Offset, AP_MAX_SENDFILE, 
                                       r->pool, c->bucket_alloc);
            while (fsize > AP_MAX_SENDFILE) {
                apr_bucket *bc;
                apr_bucket_copy(b, &bc);
                APR_BRIGADE_INSERT_TAIL(bb, bc);
                b->start += AP_MAX_SENDFILE;
                fsize -= AP_MAX_SENDFILE;
            }
            b->length = (apr_size_t)fsize; /* Resize just the last bucket */
        }
        else
#endif
            b = apr_bucket_file_create(fd, tf->Offset, (apr_size_t)fsize, 
                                       r->pool, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        
        if (tf->pTail && tf->TailLength) {
            sent += tf->TailLength;
            b = apr_bucket_transient_create((char*)tf->pTail, 
                                            tf->TailLength, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
        }
        
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        ap_pass_brigade(r->output_filters, bb);

        /* Use tf->pfnHseIO + tf->pContext, or if NULL, then use cid->fnIOComplete
         * pass pContect to the HseIO callback.
         */
        if (tf->dwFlags & HSE_IO_ASYNC) {
            if (tf->pfnHseIO) {
                if (rv == OK) {
                    tf->pfnHseIO(cid->ecb, tf->pContext, 
                                 ERROR_SUCCESS, sent);
                }
                else {
                    tf->pfnHseIO(cid->ecb, tf->pContext, 
                                 ERROR_WRITE_FAULT, sent);
                }
            }
            else if (cid->completion) {
                if (rv == OK) {
                    cid->completion(cid->ecb, cid->completion_arg, 
                                    sent, ERROR_SUCCESS);
                }
                else {
                    cid->completion(cid->ecb, cid->completion_arg, 
                                    sent, ERROR_WRITE_FAULT);
                }
            }
        }
        return (rv == OK);
    }

    case HSE_REQ_REFRESH_ISAPI_ACL:
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction "
                          "HSE_REQ_REFRESH_ISAPI_ACL "
                          "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;

    case HSE_REQ_IS_KEEP_CONN:
        *((int *)buf_data) = (r->connection->keepalive == 1);
        return 1;

    case HSE_REQ_ASYNC_READ_CLIENT:
    {
        apr_uint32_t read = 0;
        int res;
        if (!cid->dconf.fake_async) {
            if (cid->dconf.log_unsupported) 
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                            "ISAPI: asynchronous I/O not supported: %s", 
                            r->filename);
            SetLastError(ERROR_INVALID_PARAMETER);
            return 0;
        }

        if (r->remaining < *buf_size) {
            *buf_size = (apr_size_t)r->remaining;
        }

        while (read < *buf_size &&
            ((res = ap_get_client_block(r, (char*)buf_data + read,
                                        *buf_size - read)) > 0)) {
            read += res;
        }

        if ((*data_type & HSE_IO_ASYNC) && cid->completion) {
            if (res >= 0) {
                cid->completion(cid->ecb, cid->completion_arg, 
                                read, ERROR_SUCCESS);
            }
            else {
                cid->completion(cid->ecb, cid->completion_arg, 
                                read, ERROR_READ_FAULT);
            }
        }
        return (res >= 0);
    }

    case HSE_REQ_GET_IMPERSONATION_TOKEN:  /* Added in ISAPI 4.0 */
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction "
                          "HSE_REQ_GET_IMPERSONATION_TOKEN "
                          "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;

    case HSE_REQ_MAP_URL_TO_PATH_EX:
    {
        /* Map a URL to a filename */
        HSE_URL_MAPEX_INFO *info = (HSE_URL_MAPEX_INFO*)data_type;
        char* test_uri = apr_pstrndup(r->pool, (char *)buf_data, *buf_size);

        subreq = ap_sub_req_lookup_uri(test_uri, r, NULL);
        info->cchMatchingURL = strlen(test_uri);        
        info->cchMatchingPath = apr_cpystrn(info->lpszPath, subreq->filename, 
                                      sizeof(info->lpszPath)) - info->lpszPath;

        /* Mapping started with assuming both strings matched.
         * Now roll on the path_info as a mismatch and handle
         * terminating slashes for directory matches.
         */
        if (subreq->path_info && *subreq->path_info) {
