    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "clientLifetimeTimeout",
                                     CommTimeoutCbPtrFun(clientLifetimeTimeout, stream->http));
    commSetConnTimeout(clientConnection, Config.Timeout.lifetime, timeoutCall);

    stream->registerWithConn();

    // Setup Http::Request object. Maybe should be replaced by a call to (modified)
    // clientProcessRequest
    HttpRequest::Pointer request = new HttpRequest();
    AnyP::ProtocolType proto = (method == Http::METHOD_NONE) ? AnyP::PROTO_AUTHORITY_FORM : AnyP::PROTO_HTTP;
    request->url.setScheme(proto, nullptr);
    request->method = method;
    request->url.host(useHost.c_str());
    request->url.port(usePort);
    http->request = request.getRaw();
    HTTPMSGLOCK(http->request);

    request->clientConnectionManager = this;

    if (proto == AnyP::PROTO_HTTP)
        request->header.putStr(Http::HOST, useHost.c_str());
    request->flags.intercepted = ((clientConnection->flags & COMM_INTERCEPTION) != 0);
    request->flags.interceptTproxy = ((clientConnection->flags & COMM_TRANSPARENT) != 0 );
    request->sources |= ((switchedToHttps() || port->transport.protocol == AnyP::PROTO_HTTPS) ? HttpMsg::srcHttps : HttpMsg::srcHttp);
#if USE_AUTH
    if (getAuth())
        request->auth_user_request = getAuth();
#endif
    request->client_addr = clientConnection->remote;
#if FOLLOW_X_FORWARDED_FOR
    request->indirect_client_addr = clientConnection->remote;
#endif /* FOLLOW_X_FORWARDED_FOR */
    request->my_addr = clientConnection->local;
    request->myportname = port->name;

    inBuf = payload;
    flags.readMore = false;

    setLogUri(http, urlCanonicalClean(request.getRaw()));
    return http;
