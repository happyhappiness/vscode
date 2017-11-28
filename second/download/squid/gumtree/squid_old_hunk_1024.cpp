
            if (squid_curtime - http->storeEntry()->timestamp >= 86400) {
                char tbuf[512];
                snprintf (tbuf, sizeof(tbuf), "%s %s %s",
                          "113", ThisCache,
                          "This cache hit is still fresh and more than 1 day old");
                hdr->putStr(HDR_WARNING, tbuf);
            }
        }
    }

    /* RFC 2616: Section 14.18
     *
     * Add a Date: header if missing.
     * We have access to a clock therefore are required to amend any shortcoming in servers.
     *
     * NP: done after Age: to prevent ENTRY_SPECIAL double-handling this header.
     */
    if ( !hdr->has(HDR_DATE) ) {
        if (!http->storeEntry())
            hdr->insertTime(HDR_DATE, squid_curtime);
        else if (http->storeEntry()->timestamp > 0)
            hdr->insertTime(HDR_DATE, http->storeEntry()->timestamp);
        else {
            debugs(88,DBG_IMPORTANT,"BUG 3279: HTTP reply without Date:");
            /* dump something useful about the problem */
            http->storeEntry()->dump(DBG_IMPORTANT);
        }
    }

    // add Warnings required by RFC 2616 if serving a stale hit
    if (http->request->flags.staleIfHit && logTypeIsATcpHit(http->logType)) {
        hdr->putWarning(110, "Response is stale");
        if (http->request->flags.needValidation)
            hdr->putWarning(111, "Revalidation failed");
    }

    /* Filter unproxyable authentication types */
    if (http->logType != LOG_TCP_DENIED &&
            hdr->has(HDR_WWW_AUTHENTICATE)) {
        HttpHeaderPos pos = HttpHeaderInitPos;
        HttpHeaderEntry *e;

        int connection_auth_blocked = 0;
        while ((e = hdr->getEntry(&pos))) {
            if (e->id == HDR_WWW_AUTHENTICATE) {
                const char *value = e->value.rawBuf();

                if ((strncasecmp(value, "NTLM", 4) == 0 &&
                        (value[4] == '\0' || value[4] == ' '))
                        ||
                        (strncasecmp(value, "Negotiate", 9) == 0 &&
