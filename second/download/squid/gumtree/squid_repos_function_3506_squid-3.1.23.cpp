bool
ConnStateData::switchToHttps(const char *host)
{
    assert(!switchedToHttps_);

    sslHostName = host;

    //HTTPMSGLOCK(currentobject->http->request);
    assert(areAllContextsForThisConnection());
    freeAllContexts();
    //currentobject->connIsFinished();
    // We are going to read new request
    flags.readMoreRequests = true;
    debugs(33, 5, HERE << "converting FD " << fd << " to SSL");

    return getSslContextStart();
}