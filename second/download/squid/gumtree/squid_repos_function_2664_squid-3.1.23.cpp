static htcpSpecifier *
htcpUnpackSpecifier(char *buf, int sz)
{
    htcpSpecifier *s = new htcpSpecifier;
    HttpRequestMethod method;

    /* Find length of METHOD */
    u_int16_t l = ntohs(*(u_int16_t *) buf);
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

    /* Find length of URI */
    l = ntohs(*(u_int16_t *) buf);

    sz -= 2;

    if (l > sz) {
        debugs(31, 3, "htcpUnpackSpecifier: failed to unpack URI");
        htcpFreeSpecifier(s);
        return NULL;
    }

    /* Add terminating null to METHOD */
    *buf = '\0';

    /* Set URI */
    buf += 2;

    s->uri = buf;

    buf += l;

    sz -= l;

    /* Find length of VERSION */
    l = ntohs(*(u_int16_t *) buf);

    sz -= 2;

    if (l > sz) {
        debugs(31, 3, "htcpUnpackSpecifier: failed to unpack VERSION");
        htcpFreeSpecifier(s);
        return NULL;
    }

    /* Add terminating null to URI */
    *buf = '\0';

    /* Set VERSION */
    buf += 2;

    s->version = buf;

    buf += l;

    sz -= l;

    /* Find length of REQ-HDRS */
    l = ntohs(*(u_int16_t *) buf);

    sz -= 2;

    if (l > sz) {
        debugs(31, 3, "htcpUnpackSpecifier: failed to unpack REQ-HDRS");
        htcpFreeSpecifier(s);
        return NULL;
    }

    /* Add terminating null to URI */
    *buf = '\0';

    /* Set REQ-HDRS */
    buf += 2;

    s->req_hdrs = buf;

    buf += l;

    sz -= l;

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

    s->request = HttpRequest::CreateFromUrlAndMethod(s->uri, method == METHOD_NONE ? HttpRequestMethod(METHOD_GET) : method);

    if (s->request)
        HTTPMSGLOCK(s->request);

    return s;
}