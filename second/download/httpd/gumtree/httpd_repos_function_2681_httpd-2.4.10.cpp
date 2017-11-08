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
        res = ap_scan_script_header_err_strs_ex(cid->r, NULL,
                APLOG_MODULE_INDEX, &termch, &termarg, stat, head, NULL);
    }
    else {
        res = ap_scan_script_header_err_strs_ex(cid->r, NULL,
                APLOG_MODULE_INDEX, &termch, &termarg, head, NULL);
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
         * ap_scan