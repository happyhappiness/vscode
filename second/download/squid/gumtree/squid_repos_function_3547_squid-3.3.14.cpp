void
ConnStateData::quitAfterError(HttpRequest *request)
{
    // From HTTP p.o.v., we do not have to close after every error detected
    // at the client-side, but many such errors do require closure and the
    // client-side code is bad at handling errors so we play it safe.
    if (request)
        request->flags.proxyKeepalive = 0;
    flags.readMore = false;
    debugs(33,4, HERE << "Will close after error: " << clientConnection);
}