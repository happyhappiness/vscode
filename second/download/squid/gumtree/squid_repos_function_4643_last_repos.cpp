Http::Stream *
Ftp::Server::handleUserRequest(const SBuf &, SBuf &params)
{
    if (params.isEmpty())
        return earlyError(EarlyErrorKind::MissingUsername);

    // find the [end of] user name
    const SBuf::size_type eou = params.rfind('@');
    if (eou == SBuf::npos || eou + 1 >= params.length())
        return earlyError(EarlyErrorKind::MissingHost);

    // Determine the intended destination.
    host = params.substr(eou + 1, params.length());
    // If we can parse it as raw IPv6 address, then surround with "[]".
    // Otherwise (domain, IPv4, [bracketed] IPv6, garbage, etc), use as is.
    if (host.find(':') != SBuf::npos) {
        const Ip::Address ipa(host.c_str());
        if (!ipa.isAnyAddr()) {
            char ipBuf[MAX_IPSTRLEN];
            ipa.toHostStr(ipBuf, MAX_IPSTRLEN);
            host = ipBuf;
        }
    }

    // const SBuf login = params.substr(0, eou);
    params.chop(0, eou); // leave just the login part for the peer

    SBuf oldUri;
    if (master->clientReadGreeting)
        oldUri = uri;

    master->workingDir.clear();
    calcUri(NULL);

    if (!master->clientReadGreeting) {
        debugs(9, 3, "set URI to " << uri);
    } else if (oldUri.caseCmp(uri) == 0) {
        debugs(9, 5, "kept URI as " << oldUri);
    } else {
        debugs(9, 3, "reset URI from " << oldUri << " to " << uri);
        closeDataConnection();
        unpinConnection(true); // close control connection to peer
        resetLogin("URI reset");
    }

    return NULL; // no early errors
}