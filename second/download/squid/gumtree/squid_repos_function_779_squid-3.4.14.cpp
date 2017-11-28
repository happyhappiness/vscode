void
ClientHttpRequest::processRequest()
{
    debugs(85, 4, "clientProcessRequest: " << RequestMethodStr(request->method) << " '" << uri << "'");

    if (request->method == Http::METHOD_CONNECT && !redirect.status) {
#if USE_SSL
        if (sslBumpNeeded()) {
            sslBumpStart();
            return;
        }
#endif
        logType = LOG_TCP_MISS;
        getConn()->stopReading(); // tunnels read for themselves
        tunnelStart(this, &out.size, &al->http.code, al);
        return;
    }

    httpStart();
}