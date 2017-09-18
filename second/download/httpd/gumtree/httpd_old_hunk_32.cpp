         * XxX: As everywhere, EXEC flags could use some work...
         *      and this could go further with more flags, as desired.
         */ 
        info->dwFlags = (subreq->finfo.protection & APR_UREAD    ? 0x001 : 0)
                      | (subreq->finfo.protection & APR_UWRITE   ? 0x002 : 0)
                      | (subreq->finfo.protection & APR_UEXECUTE ? 0x204 : 0);
        return TRUE;
    }
#endif

    case 1014: /* HSE_REQ_ABORTIVE_CLOSE */
        if (cid->sconf->LogNotSupported)
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI ServerSupportFunction HSE_REQ_ABORTIVE_CLOSE"
                          " is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;

    case 1015: /* HSE_REQ_GET_CERT_INFO_EX  Added in ISAPI 4.0 */
        if (cid->sconf->LogNotSupported)
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI ServerSupportFunction "
                          "HSE_REQ_GET_CERT_INFO_EX "
                          "is not supported: %s", r->filename);        
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;

#ifdef HSE_REQ_SEND_RESPONSE_HEADER_EX
    case 1016: /* HSE_REQ_SEND_RESPONSE_HEADER_EX  Added in ISAPI 4.0 */
    {
        LPHSE_SEND_HEADER_EX_INFO shi
                                  = (LPHSE_SEND_HEADER_EX_INFO) lpvBuffer;
        /* XXX: ignore shi->fKeepConn?  We shouldn't need the advise */
        /* r->connection->keepalive = shi->fKeepConn; */
        apr_ssize_t ate = SendResponseHeaderEx(cid, shi->pszStatus, 
                                               shi->pszHeader,
                                               shi->cchStatus, 
                                               shi->cchHeader);
        if (ate < 0) {
            SetLastError(TODO_ERROR);
            return FALSE;
        }
        else if ((apr_size_t)ate < shi->cchHeader) {
            apr_bucket_brigade *bb;
            apr_bucket *b;
            bb = apr_brigade_create(cid->r->pool, c->bucket_alloc);
	    b = apr_bucket_transient_create(shi->pszHeader + ate, 
