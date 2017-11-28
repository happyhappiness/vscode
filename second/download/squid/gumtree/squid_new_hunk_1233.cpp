    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "clientLifetimeTimeout",
                                     CommTimeoutCbPtrFun(clientLifetimeTimeout, stream->http));
    commSetConnTimeout(clientConnection, Config.Timeout.lifetime, timeoutCall);

    stream->registerWithConn();

    MasterXaction::Pointer mx = new MasterXaction(XactionInitiator::initClient);
    mx->tcpClient = clientConnection;
    // Setup Http::Request object. Maybe should be replaced by a call to (modified)
    // clientProcessRequest
    HttpRequest::Pointer request = new HttpRequest(mx);
    AnyP::ProtocolType proto = (method == Http::METHOD_NONE) ? AnyP::PROTO_AUTHORITY_FORM : AnyP::PROTO_HTTP;
    request->url.setScheme(proto, nullptr);
    request->method = method;
    request->url.host(useHost.c_str());
    request->url.port(usePort);
    http->request = request.getRaw();
    HTTPMSGLOCK(http->request);

    request->manager(this, http->al);

    if (proto == AnyP::PROTO_HTTP)
        request->header.putStr(Http::HOST, useHost.c_str());

    request->sources |= ((switchedToHttps() || port->transport.protocol == AnyP::PROTO_HTTPS) ? HttpMsg::srcHttps : HttpMsg::srcHttp);
#if USE_AUTH
    if (getAuth())
        request->auth_user_request = getAuth();
#endif

    inBuf = payload;
    flags.readMore = false;

    setLogUri(http, urlCanonicalClean(request.getRaw()));
    return http;
