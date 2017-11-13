static apr_ssize_t send_response_header(isapi_cid *cid,
                                        const char *stat,
                                        const char *head,
                                        apr_size_t statlen,
                                        apr_size_t headlen)
{
    int head_present = 1;
    int termarg;
    int res;
    int old_status;
    const char *termch;
    apr_size_t ate = 0;

    if (!head || headlen == 0 || !*head) {
        head = stat;
        stat = NULL;
        headlen = statlen;
        statlen = 0;
        head_present = 0; /* Don't eat the header */
    }

    if (!stat || statlen == 0 || !*stat) {
        if (head && headlen && *head && ((stat = memchr(head, '\r', headlen))
                                      || (stat = memchr(head, '\n', headlen))
                                      || (stat = memchr(head, '\0', headlen))
                                      || (stat = head + headlen))) {
            statlen = stat - head;
            if (memchr(head, ':', statlen)) {
                stat = "Status: 200 OK";
                statlen = strlen(stat);
            }
            else {
                const char *flip = head;
                head = stat;
                stat = flip;
                headlen -= statlen;
                ate += statlen;
                if (*head == '\r' && headlen)
                    ++head, --headlen, ++ate;
                if (*head == '\n' && headlen)
                    ++head, --headlen, ++ate;
            }
        }
    }

    if (stat && (statlen > 0) && *stat) {
        char *newstat;
        if (!apr_isdigit(*stat)) {
            const char *stattok = stat;
            int toklen = statlen;
            while (toklen && *stattok && !apr_isspace(*stattok)) {
                ++stattok; --toklen;
            }
            while (toklen && apr_isspace(*stattok)) {
                ++stattok; --toklen;
            }
            /* Now decide if we follow the xxx message
             * or the http/x.x xxx message format
             */
            if (toklen && apr_isdigit(*stattok)) {
                statlen = toklen;
                stat = stattok;
            }
        }
        newstat = apr_palloc(cid->r->pool, statlen + 9);
        strcpy(newstat, "Status: ");
        apr_cpystrn(newstat + 8, stat, statlen + 1);
        stat = newstat;
        statlen += 8;
    }

    if (!head || headlen == 0 || !*head) {
        head = "\r\n";
        headlen = 2;
    }
    else
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
    old_status = cid->r->status;

    if (stat) {
        res = ap_scan_script_header_err_strs(cid->r, NULL, &termch, &termarg,
                stat, head, NULL);
    }
    else {
        res = ap_scan_script_header_err_strs(cid->r, NULL, &termch, &termarg,
                head, NULL);
    }

    /* Set our status. */
    if (res) {
        /* This is an immediate error result from the parser
         */
        cid->r->status = res;
        cid->r->status_line = ap_get_status_line(cid->r->status);
        cid->ecb->dwHttpStatusCode = cid->r->status;
    }
    else if (cid->r->status) {
        /* We have a status in r->status, so let's just use it.
         * This is likely to be the Status: parsed above, and
         * may also be a delayed error result from the parser.
         * If it was filled in, status_line should also have
         * been filled in.
         */
        cid->ecb->dwHttpStatusCode = cid->r->status;
    }
    else if (cid->ecb->dwHttpStatusCode
              && cid->ecb->dwHttpStatusCode != HTTP_OK) {
        /* Now we fall back on dwHttpStatusCode if it appears
         * ap_scan_script_header fell back on the default code.
         * Any other results set dwHttpStatusCode to the decoded
         * status value.
         */
        cid->r->status = cid->ecb->dwHttpStatusCode;
        cid->r->status_line = ap_get_status_line(cid->r->status);
    }
    else if (old_status) {
        /* Well... either there is no dwHttpStatusCode or it's HTTP_OK.
         * In any case, we don't have a good status to return yet...
         * Perhaps the one we came in with will be better. Let's use it,
         * if we were given one (note this is a pendantic case, it would
         * normally be covered above unless the scan script code unset
         * the r->status). Should there be a check here as to whether
         * we are setting a valid response code?
         */
        cid->r->status = old_status;
        cid->r->status_line = ap_get_status_line(cid->r->status);
        cid->ecb->dwHttpStatusCode = cid->r->status;
    }
    else {
        /* None of dwHttpStatusCode, the parser's r->status nor the 
         * old value of r->status were helpful, and nothing was decoded
         * from Status: string passed to us.  Let's just say HTTP_OK 
         * and get the data out, this was the isapi dev's oversight.
         */
        cid->r->status = HTTP_OK;
        cid->r->status_line = ap_get_status_line(cid->r->status);
        cid->ecb->dwHttpStatusCode = cid->r->status;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, cid->r,
                "ISAPI: Could not determine HTTP response code; using %d",
                cid->r->status);
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
     * happens if the parser got to the head arg, which varies based
     * on whether we passed stat+head to scan, or only head.
     */
    if (termch && (termarg == (stat ? 1 : 0))
               && head_present && head + headlen > termch) {
        return ate + termch - head;
    }
    return ate;
}