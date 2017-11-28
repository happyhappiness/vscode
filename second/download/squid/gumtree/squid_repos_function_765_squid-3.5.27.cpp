void
ClientHttpRequest::processRequest()
{
    debugs(85, 4, request->method << ' ' << uri);

    if (request->method == Http::METHOD_CONNECT && !redirect.status) {
#if USE_OPENSSL
        if (sslBumpNeeded()) {
            sslBumpStart();
            return;
        }
#endif
        getConn()->stopReading(); // tunnels read for themselves
        tunnelStart(this);
        return;
    }

    httpStart();
}