static int APR_THREAD_FUNC regfnServerSupportFunction(isapi_cid    *cid,
                                                      apr_uint32_t  HSE_code,
                                                      void         *buf_ptr,
                                                      apr_uint32_t *buf_size,
                                                      apr_uint32_t *data_type)
{
    request_rec *r = cid->r;
    conn_rec *c = r->connection;
    char *buf_data = (char*)buf_ptr;
    request_rec *subreq;
    apr_status_t rv;

    switch (HSE_code) {
    case HSE_REQ_SEND_URL_REDIRECT_RESP:
        /* Set the status to be returned when the HttpExtensionProc()
         * is done.
         * WARNING: Microsoft now advertises HSE_REQ_SEND_URL_REDIRECT_RESP
         *          and HSE_REQ_SEND_URL as equivalent per the Jan 2000 SDK.
         *          They most definitely are not, even in their own samples.
         */
        apr_table_set (r->headers_out, "Location", buf_data);
        cid->r->status = cid->ecb->dwHttpStatusCode = HTTP_MOVED_TEMPORARILY;
        cid->r->status_line = ap_get_status_line(cid->r->status);
        cid->headers_set = 1;
        return 1;

    case HSE_REQ_SEND_URL:
        /* Soak up remaining input */
        if (r->remaining > 0) {
            char argsbuffer[HUGE_STRING_LEN];
            while (ap_get_client_block(r, argsbuffer, HUGE_STRING_LEN));
        }

        /* Reset the method to GET */
        r->method = "GET";
        r->method_number = M_GET;

        /* Don't let anyone think there's still data */
        apr_table_unset(r->headers_in, "Content-Length");

        /* AV fault per PR3598 - redirected path is lost! */
        buf_data = apr_pstrdup(r->pool, (char*)buf_data);
        ap_internal_redirect(buf_data, r);
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
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
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
            rv = ap_pass_brigade(cid->r->output_filters, bb);
            cid->response_sent = 1;
            if (rv != APR_SUCCESS)
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                              "ServerSupport function "
                              "HSE_REQ_SEND_RESPONSE_HEADER "
                              "ap_pass_brigade failed: %s", r->filename);
            return (rv == APR_SUCCESS);
        }
        /* Deliberately hold off sending 'just the headers' to begin to
         * accumulate the body and speed up the overall response, or at
         * least wait for the end the session.
         */
        return 1;
    }

    case HSE_REQ_DONE_WITH_SESSION:
        /* Signal to resume the thread completing this request,
         * leave it to the pool cleanup to dispose of our mutex.
         */
        if (cid->completed) {
            (void)apr_thread_mutex_unlock(cid->completed);
            return 1;
        }
        else if (cid->dconf.log_unsupported) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02671)
                          "ServerSupportFunction "
                          "HSE_REQ_DONE_WITH_SESSION is not supported: %s",
                          r->filename);
        }
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;

    case HSE_REQ_MAP_URL_TO_PATH:
    {
        /* Map a URL to a filename */
        char *file = (char *)buf_data;
        apr_uint32_t len;
        subreq = ap_sub_req_lookup_uri(
                     apr_pstrndup(cid->r->pool, file, *buf_size), r, NULL);

        if (!subreq->filename) {
            ap_destroy_sub_req(subreq);
            return 0;
        }

        len = (apr_uint32_t)strlen(r->filename);

        if ((subreq->finfo.filetype == APR_DIR)
              && (!subreq->path_info)
              && (file[len - 1] != '/'))
            file = apr_pstrcat(cid->r->pool, subreq->filename, "/", NULL);
        else
            file = apr_pstrcat(cid->r->pool, subreq->filename,
                                              subreq->path_info, NULL);

        ap_destroy_sub_req(subreq);

#ifdef WIN32
        /* We need to make this a real Windows path name */
        apr_filepath_merge(&file, "", file, APR_FILEPATH_NATIVE, r->pool);
#endif

        *buf_size = apr_cpystrn(buf_data, file, *buf_size) - buf_data;

        return 1;
    }

    case HSE_REQ_GET_SSPI_INFO:
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02672)
                           "ServerSupportFunction HSE_REQ_GET_SSPI_INFO "
                           "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
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
                          "%s: %s", cid->r->filename,
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
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02673)
                      "ServerSupportFunction HSE_REQ_IO_COMPLETION "
                      "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;

    case HSE_REQ_TRANSMIT_FILE:
    {
        /* we do nothing with (tf->dwFlags & HSE_DISCONNECT_AFTER_SEND)
         */
        HSE_TF_INFO *tf = (HSE_TF_INFO*)buf_data;
        apr_uint32_t sent = 0;
        apr_ssize_t ate = 0;
        apr_bucket_brigade *bb;
        apr_bucket *b;
        apr_file_t *fd;
        apr_off_t fsize;

        if (!cid->dconf.fake_async && (tf->dwFlags & HSE_IO_ASYNC)) {
            if (cid->dconf.log_unsupported)
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02674)
                         "ServerSupportFunction HSE_REQ_TRANSMIT_FILE "
                         "as HSE_IO_ASYNC is not supported: %s", r->filename);
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
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
                apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
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
        else if (!cid->headers_set && tf->pHead && tf->HeadLength
                                   && *(char*)tf->pHead) {
            ate = send_response_header(cid, NULL, (char*)tf->pHead,
                                            0, tf->HeadLength);
            if (ate < 0)
            {
                apr_brigade_destroy(bb);
                apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
                return 0;
            }
        }

        if (tf->pHead && (apr_size_t)ate < tf->HeadLength) {
            b = apr_bucket_transient_create((char*)tf->pHead + ate,
                                            tf->HeadLength - ate,
                                            c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
            sent = tf->HeadLength;
        }

        sent += (apr_uint32_t)fsize;
        apr_brigade_insert_file(bb, fd, tf->Offset, fsize, r->pool);

        if (tf->pTail && tf->TailLength) {
            sent += tf->TailLength;
            b = apr_bucket_transient_create((char*)tf->pTail,
                                            tf->TailLength, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
        }

        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        cid->response_sent = 1;
        if (rv != APR_SUCCESS)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "ServerSupport function "
                          "HSE_REQ_TRANSMIT_FILE "
                          "ap_pass_brigade failed: %s", r->filename);

        /* Use tf->pfnHseIO + tf->pContext, or if NULL, then use cid->fnIOComplete
         * pass pContect to the HseIO callback.
         */
        if (tf->dwFlags & HSE_IO_ASYNC) {
            if (tf->pfnHseIO) {
                if (rv == APR_SUCCESS) {
                    tf->pfnHseIO(cid->ecb, tf->pContext,
                                 ERROR_SUCCESS, sent);
                }
                else {
                    tf->pfnHseIO(cid->ecb, tf->pContext,
                                 ERROR_WRITE_FAULT, sent);
                }
            }
            else if (cid->completion) {
                if (rv == APR_SUCCESS) {
                    cid->completion(cid->ecb, cid->completion_arg,
                                    sent, ERROR_SUCCESS);
                }
                else {
                    cid->completion(cid->ecb, cid->completion_arg,
                                    sent, ERROR_WRITE_FAULT);
                }
            }
        }
        return (rv == APR_SUCCESS);
    }

    case HSE_REQ_REFRESH_ISAPI_ACL:
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02675)
                          "ServerSupportFunction "
                          "HSE_REQ_REFRESH_ISAPI_ACL "
                          "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;

    case HSE_REQ_IS_KEEP_CONN:
        *((int *)buf_data) = (r->connection->keepalive == AP_CONN_KEEPALIVE);
        return 1;

    case HSE_REQ_ASYNC_READ_CLIENT:
    {
        apr_uint32_t read = 0;
        int res = 0;
        if (!cid->dconf.fake_async) {
            if (cid->dconf.log_unsupported)
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                            "asynchronous I/O not supported: %s",
                            r->filename);
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
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
            /* XXX: Many authors issue their next HSE_REQ_ASYNC_READ_CLIENT
             * within the completion logic.  An example is MS's own PSDK
             * sample web/iis/extensions/io/ASyncRead.  This potentially
             * leads to stack exhaustion.  To refactor, the notification
             * logic needs to move to isapi_handler() - differentiating
             * the cid->completed event with a new flag to indicate
             * an async-notice versus the async request completed.
             */
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
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02676)
                          "ServerSupportFunction "
                          "HSE_REQ_GET_IMPERSONATION_TOKEN "
                          "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
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
            apr_cpystrn(info->lpszPath + info->cchMatchingPath,
                        subreq->path_info,
                        sizeof(info->lpszPath) - info->cchMatchingPath);
            info->cchMatchingURL -= strlen(subreq->path_info);
            if (subreq->finfo.filetype == APR_DIR
                 && info->cchMatchingPath < sizeof(info->lpszPath) - 1) {
                /* roll forward over path_info's first slash */
                ++info->cchMatchingPath;
                ++info->cchMatchingURL;
            }
        }
        else if (subreq->finfo.filetype == APR_DIR
                 && info->cchMatchingPath < sizeof(info->lpszPath) - 1) {
            /* Add a trailing slash for directory */
            info->lpszPath[info->cchMatchingPath++] = '/';
            info->lpszPath[info->cchMatchingPath] = '\0';
        }

        /* If the matched isn't a file, roll match back to the prior slash */
        if (subreq->finfo.filetype == APR_NOFILE) {
            while (info->cchMatchingPath && info->cchMatchingURL) {
                if (info->lpszPath[info->cchMatchingPath - 1] == '/')
                    break;
                --info->cchMatchingPath;
                --info->cchMatchingURL;
            }
        }

        /* Paths returned with back slashes */
        for (test_uri = info->lpszPath; *test_uri; ++test_uri)
            if (*test_uri == '/')
                *test_uri = '\\';

        /* is a combination of:
         * HSE_URL_FLAGS_READ         0x001 Allow read
         * HSE_URL_FLAGS_WRITE        0x002 Allow write
         * HSE_URL_FLAGS_EXECUTE      0x004 Allow execute
         * HSE_URL_FLAGS_SSL          0x008 Require SSL
         * HSE_URL_FLAGS_DONT_CACHE   0x010 Don't cache (VRoot only)
         * HSE_URL_FLAGS_NEGO_CERT    0x020 Allow client SSL cert
         * HSE_URL_FLAGS_REQUIRE_CERT 0x040 Require client SSL cert
         * HSE_URL_FLAGS_MAP_CERT     0x080 Map client SSL cert to account
         * HSE_URL_FLAGS_SSL128       0x100 Require 128-bit SSL cert
         * HSE_URL_FLAGS_SCRIPT       0x200 Allow script execution
         *
         * XxX: As everywhere, EXEC flags could use some work...
         *      and this could go further with more flags, as desired.
         */
        info->dwFlags = (subreq->finfo.protection & APR_UREAD    ? 0x001 : 0)
                      | (subreq->finfo.protection & APR_UWRITE   ? 0x002 : 0)
                      | (subreq->finfo.protection & APR_UEXECUTE ? 0x204 : 0);
        return 1;
    }

    case HSE_REQ_ABORTIVE_CLOSE:
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02677)
                          "ServerSupportFunction HSE_REQ_ABORTIVE_CLOSE"
                          " is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;

    case HSE_REQ_GET_CERT_INFO_EX:  /* Added in ISAPI 4.0 */
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02678)
                          "ServerSupportFunction "
                          "HSE_REQ_GET_CERT_INFO_EX "
                          "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;

    case HSE_REQ_SEND_RESPONSE_HEADER_EX:  /* Added in ISAPI 4.0 */
    {
        HSE_SEND_HEADER_EX_INFO *shi = (HSE_SEND_HEADER_EX_INFO*)buf_data;

        /*  Ignore shi->fKeepConn - we don't want the advise
         */
        apr_ssize_t ate = send_response_header(cid, shi->pszStatus,
                                               shi->pszHeader,
                                               shi->cchStatus,
                                               shi->cchHeader);
        if (ate < 0) {
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
            return 0;
        }
        else if ((apr_size_t)ate < shi->cchHeader) {
            apr_bucket_brigade *bb;
            apr_bucket *b;
            bb = apr_brigade_create(cid->r->pool, c->bucket_alloc);
            b = apr_bucket_transient_create(shi->pszHeader + ate,
                                            shi->cchHeader - ate,
                                            c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
            b = apr_bucket_flush_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
            rv = ap_pass_brigade(cid->r->output_filters, bb);
            cid->response_sent = 1;
            if (rv != APR_SUCCESS)
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                              "ServerSupport function "
                              "HSE_REQ_SEND_RESPONSE_HEADER_EX "
                              "ap_pass_brigade failed: %s", r->filename);
            return (rv == APR_SUCCESS);
        }
        /* Deliberately hold off sending 'just the headers' to begin to
         * accumulate the body and speed up the overall response, or at
         * least wait for the end the session.
         */
        return 1;
    }

    case HSE_REQ_CLOSE_CONNECTION:  /* Added after ISAPI 4.0 */
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02679)
                          "ServerSupportFunction "
                          "HSE_REQ_CLOSE_CONNECTION "
                          "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
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
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02680)
                          "ServerSupportFunction "
                          "HSE_REQ_EXTENSION_TRIGGER "
                          "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;

    default:
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02681)
                          "ServerSupportFunction (%d) not supported: "
                          "%s", HSE_code, r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;
    }
}