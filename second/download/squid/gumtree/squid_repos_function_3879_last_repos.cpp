void Ssl::Helper::sslSubmit(CrtdMessage const & message, HLPCB * callback, void * data)
{
    assert(ssl_crtd);

    SBuf rawMessage(message.compose().c_str()); // XXX: helpers cannot use SBuf
    rawMessage.append("\n", 1);

    const auto pending = TheGeneratorRequests.find(rawMessage);
    if (pending != TheGeneratorRequests.end()) {
        pending->second->emplace(callback, data);
        debugs(83, 5, "collapsed request from " << data << " onto " << *pending->second);
        return;
    }

    GeneratorRequest *request = new GeneratorRequest;
    request->query = rawMessage;
    request->emplace(callback, data);
    TheGeneratorRequests.emplace(request->query, request);
    debugs(83, 5, "request from " << data << " as " << *request);
    if (ssl_crtd->trySubmit(request->query.c_str(), HandleGeneratorReply, request))
        return;

    ::Helper::Reply failReply(::Helper::BrokenHelper);
    failReply.notes.add("message", "error 45 Temporary network problem, please retry later");
    HandleGeneratorReply(request, failReply);
}