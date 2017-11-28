void
ClientHttpRequest::processRequest()
{
    debugs(85, 4, request->method << ' ' << uri);

    const bool untouchedConnect = request->method == Http::METHOD_CONNECT && !redirect.status;

#if USE_OPENSSL
    if (untouchedConnect && sslBumpNeeded()) {
        assert(!request->flags.forceTunnel);
        sslBumpStart();
        return;
    }
#endif

    if (untouchedConnect || request->flags.forceTunnel) {
        getConn()->stopReading(); // tunnels read for themselves
        tunnelStart(this);
        return;
    }

    httpStart();
}