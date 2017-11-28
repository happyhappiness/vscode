bool clientExpectsConnectResponse() const {
#if USE_OPENSSL
        // We are bumping and we had already send "OK CONNECTED"
        if (http.valid() && http->getConn() && http->getConn()->serverBump() && http->getConn()->serverBump()->step > Ssl::bumpStep1)
            return false;
#endif
        return !(request != NULL &&
                 (request->flags.interceptTproxy || request->flags.intercepted));
    }