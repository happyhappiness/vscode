static void
httpsSslBumpAccessCheckDone(allow_t answer, void *data)
{
    ConnStateData *connState = (ConnStateData *) data;

    // if the connection is closed or closing, just return.
    if (!connState->isOpen())
        return;

    // Require both a match and a positive bump mode to work around exceptional
    // cases where ACL code may return ACCESS_ALLOWED with zero answer.kind.
    if (answer == ACCESS_ALLOWED && (answer.kind != Ssl::bumpNone && answer.kind != Ssl::bumpSplice)) {
        debugs(33, 2, "sslBump needed for " << connState->clientConnection << " method " << answer.kind);
        connState->sslBumpMode = static_cast<Ssl::BumpMode>(answer.kind);
    } else {
        debugs(33, 2, HERE << "sslBump not needed for " << connState->clientConnection);
        connState->sslBumpMode = Ssl::bumpNone;
    }
    connState->fakeAConnectRequest("ssl-bump", connState->in.buf);
}