static htcpSpecifier *
htcpUnpackSpecifier(char *buf, int sz)
{
    htcpSpecifier *s = new htcpSpecifier;
    HttpRequestMethod method;

    /* Find length of METHOD */
    uint16_t l = ntohs(*(uint16_t *) buf);
    sz -= 2;
    buf += 2;

    if (l > sz) {
        debugs(31, 3, "htcpUnpackSpecifier: failed to unpack METHOD");
        htcpFreeSpecifier(s);
        return NULL;
    }

    /* Set METHOD */
    s->method = buf;
    buf += l;
    sz -= l;
    debugs(31, 6, "htcpUnpackSpecifier: METHOD (" << l << "/" << sz << ") '" << s->method << "'");

    /* Find length of URI */
    l = ntohs(*(uint16_t *) buf);
    sz -= 2;

    if (l > sz) {
        debugs(31, 3, "htcpUnpackSpecifier: failed to unpack URI");
        htcpFreeSpecifier(s);
        return NULL;
    }

    /* Add terminating null to METHOD */
    *buf = '\0';
    buf += 2;

    /* Set URI */
    s->uri = buf;
    buf += l;
    sz -= l;
    debugs(31, 6, "htcpUnpackSpecifier: URI (" << l << "/" << sz << ") '" << s->uri << "'");

    /* Find length of VERSION */
    l = ntohs(*(uint16_t *) buf);
    sz -= 2;

    if (l > sz) {
        debugs(31, 3, "htcpUnpackSpecifier: failed to unpack VERSION");
        htcpFreeSpecifier(s);
        return NULL;
    }

    /* Add terminating null to URI */
    *buf = '\0';
    buf += 2;

    /* Set VERSION */
    s->version = buf;
    buf += l;
    sz -= l;
    debugs(31, 6, "htcpUnpackSpecifier: VERSION (" << l << "/" << sz << ") '" << s->version << "'");

    /* Find length of REQ-HDRS */
    l = ntohs(*(uint16_t *) buf);
    sz -= 2;

    if (l > sz) {
        debugs(31, 3, "htcpUnpackSpecifier: failed to unpack REQ-HDRS");
        htcpFreeSpecifier(s);
        return NULL;
    }

    /* Add terminating null to URI */
    *buf = '\0';
    buf += 2;

    /* Set REQ-HDRS */
    s->req_hdrs = buf;
    buf += l;
    sz -= l;
    debugs(31, 6, "htcpUnpackSpecifier: REQ-HDRS (" << l << "/" << sz << ") '" << s->req_hdrs << "'");

    debugs(31, 3, "htcpUnpackSpecifier: " << sz << " bytes left");

    /*
     * Add terminating null to REQ-HDRS. This is possible because we allocated
     * an extra byte when we received the packet. This will overwrite any following
     * AUTH block.
     */
    *buf = '\0';

    /*
     * Parse the request
     */
    method = HttpRequestMethod(s->method, NULL);

    s->request = HttpRequest::CreateFromUrlAndMethod(s->uri, method == Http::METHOD_NONE ? HttpRequestMethod(Http::METHOD_GET) : method);

    if (s->request)
        HTTPMSGLOCK(s->request);

    return s;
}