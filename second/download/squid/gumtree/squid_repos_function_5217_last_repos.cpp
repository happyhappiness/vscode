static void
purgeEntriesByHeader(HttpRequest *req, const char *reqUrl, HttpMsg *rep, Http::HdrType hdr)
{
    const char *hdrUrl, *absUrl;

    absUrl = NULL;
    hdrUrl = rep->header.getStr(hdr);
    if (hdrUrl == NULL) {
        return;
    }

    /*
     * If the URL is relative, make it absolute so we can find it.
     * If it's absolute, make sure the host parts match to avoid DOS attacks
     * as per RFC 2616 13.10.
     */
    if (urlIsRelative(hdrUrl)) {
        absUrl = urlMakeAbsolute(req, hdrUrl);
        if (absUrl != NULL) {
            hdrUrl = absUrl;
        }
    } else if (!sameUrlHosts(reqUrl, hdrUrl)) {
        return;
    }

    purgeEntriesByUrl(req, hdrUrl);

    if (absUrl != NULL) {
        safe_free(absUrl);
    }
}