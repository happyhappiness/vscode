static void
clientCheckPinning(ClientHttpRequest * http)
{
    HttpRequest *request = http->request;
    HttpHeader *req_hdr = &request->header;
    ConnStateData *http_conn = http->getConn();

    /* Internal requests such as those from ESI includes may be without
     * a client connection
     */
    if (!http_conn)
        return;

    request->flags.connectionAuthDisabled = http_conn->port->connection_auth_disabled;
    if (!request->flags.connectionAuthDisabled) {
        if (Comm::IsConnOpen(http_conn->pinning.serverConnection)) {
            if (http_conn->pinning.auth) {
                request->flags.connectionAuth = true;
                request->flags.auth = true;
            } else {
                request->flags.connectionProxyAuth = true;
            }
            // These should already be linked correctly.
            assert(request->clientConnectionManager == http_conn);
        }
    }

    /* check if connection auth is used, and flag as candidate for pinning
     * in such case.
     * Note: we may need to set flags.connectionAuth even if the connection
     * is already pinned if it was pinned earlier due to proxy auth
     */
    if (!request->flags.connectionAuth) {
        if (req_hdr->has(Http::HdrType::AUTHORIZATION) || req_hdr->has(Http::HdrType::PROXY_AUTHORIZATION)) {
            HttpHeaderPos pos = HttpHeaderInitPos;
            HttpHeaderEntry *e;
            int may_pin = 0;
            while ((e = req_hdr->getEntry(&pos))) {
                if (e->id == Http::HdrType::AUTHORIZATION || e->id == Http::HdrType::PROXY_AUTHORIZATION) {
                    const char *value = e->value.rawBuf();
                    if (strncasecmp(value, "NTLM ", 5) == 0
                            ||
                            strncasecmp(value, "Negotiate ", 10) == 0
                            ||
                            strncasecmp(value, "Kerberos ", 9) == 0) {
                        if (e->id == Http::HdrType::AUTHORIZATION) {
                            request->flags.connectionAuth = true;
                            may_pin = 1;
                        } else {
                            request->flags.connectionProxyAuth = true;
                            may_pin = 1;
                        }
                    }
                }
            }
            if (may_pin && !request->pinnedConnection()) {
                // These should already be linked correctly. Just need the ServerConnection to pinn.
                assert(request->clientConnectionManager == http_conn);
            }
        }
    }
}