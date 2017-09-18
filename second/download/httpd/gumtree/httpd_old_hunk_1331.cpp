    {
        if (head[headlen - 1] && head[headlen]) {
            /* Whoops... not NULL terminated */
            head = apr_pstrndup(cid->r->pool, head, headlen);
        }
    }
 
    /* Seems IIS does not enforce the requirement for \r\n termination 
     * on HSE_REQ_SEND_RESPONSE_HEADER, but we won't panic... 
     * ap_scan_script_header_err_strs handles this aspect for us.
     *
     * Parse them out, or die trying 
     */
    if (stat) {
        cid->r->status = ap_scan_script_header_err_strs(cid->r, NULL, 
                                        &termch, &termarg, stat, head, NULL);
        cid->ecb->dwHttpStatusCode = cid->r->status;
    }
    else {
        cid->r->status = ap_scan_script_header_err_strs(cid->r, NULL, 
                                        &termch, &termarg, head, NULL);
        if (cid->ecb->dwHttpStatusCode && cid->r->status == HTTP_OK
                && cid->ecb->dwHttpStatusCode != HTTP_OK) {
            /* We tried every way to Sunday to get the status...
             * so now we fall back on dwHttpStatusCode if it appears
             * ap_scan_script_header fell back on the default code.
             * Any other results set dwHttpStatusCode to the decoded 
             * status value.
             */
            cid->r->status = cid->ecb->dwHttpStatusCode;
            cid->r->status_line = ap_get_status_line(cid->r->status);
        }
        else {
            cid->ecb->dwHttpStatusCode = cid->r->status;
        }
    }
    if (cid->r->status == HTTP_INTERNAL_SERVER_ERROR) {
        return -1;
    }

    /* If only Status was passed, we consumed nothing 
     */
    if (!head_present)
        return 0;

    cid->headers_set = 1;

    /* If all went well, tell the caller we consumed the headers complete 
     */
    if (!termch)
        return(ate + headlen);

    /* Any data left must be sent directly by the caller, all we
     * give back is the size of the headers we consumed (which only
