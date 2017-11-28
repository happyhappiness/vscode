bool
Ssl::PeekingPeerConnector::initialize(Security::SessionPointer &serverSession)
{
    if (!Security::PeerConnector::initialize(serverSession))
        return false;

    if (ConnStateData *csd = request->clientConnectionManager.valid()) {

        // client connection is required in the case we need to splice
        // or terminate client and server connections
        assert(clientConn != NULL);
        SBuf *hostName = NULL;

        //Enable Status_request TLS extension, required to bump some clients
        SSL_set_tlsext_status_type(serverSession.get(), TLSEXT_STATUSTYPE_ocsp);

        const Security::TlsDetails::Pointer details = csd->tlsParser.details;
        if (details && !details->serverName.isEmpty())
            hostName = new SBuf(details->serverName);

        if (!hostName) {
            // While we are peeking at the certificate, we may not know the server
            // name that the client will request (after interception or CONNECT)
            // unless it was the CONNECT request with a user-typed address.
            const bool isConnectRequest = !csd->port->flags.isIntercepted();
            if (!request->flags.sslPeek || isConnectRequest)
                hostName = new SBuf(request->url.host());
        }

        if (hostName)
            SSL_set_ex_data(serverSession.get(), ssl_ex_index_server, (void*)hostName);

        Must(!csd->serverBump() || csd->serverBump()->step <= Ssl::bumpStep2);
        if (csd->sslBumpMode == Ssl::bumpPeek || csd->sslBumpMode == Ssl::bumpStare) {
            auto clientSession = fd_table[clientConn->fd].ssl.get();
            Must(clientSession);
            BIO *bc = SSL_get_rbio(clientSession);
            Ssl::ClientBio *cltBio = static_cast<Ssl::ClientBio *>(BIO_get_data(bc));
            Must(cltBio);
            if (details && details->tlsVersion.protocol != AnyP::PROTO_NONE)
                applyTlsDetailsToSSL(serverSession.get(), details, csd->sslBumpMode);

            BIO *b = SSL_get_rbio(serverSession.get());
            Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(BIO_get_data(b));
            Must(srvBio);
            // inherit client features such as TLS version and SNI
            srvBio->setClientFeatures(details, cltBio->rBufData());
            srvBio->recordInput(true);
            srvBio->mode(csd->sslBumpMode);
        } else {
            // Set client SSL options
            SSL_set_options(serverSession.get(), ::Security::ProxyOutgoingConfig.parsedOptions);

            // Use SNI TLS extension only when we connect directly
            // to the origin server and we know the server host name.
            const char *sniServer = NULL;
            const bool redirected = request->flags.redirected && ::Config.onoff.redir_rewrites_host;
            if (!hostName || redirected)
                sniServer = !request->url.hostIsNumeric() ? request->url.host() : NULL;
            else
                sniServer = hostName->c_str();

            if (sniServer)
                Ssl::setClientSNI(serverSession.get(), sniServer);
        }

        if (Ssl::ServerBump *serverBump = csd->serverBump()) {
            serverBump->attachServerSession(serverSession);
            // store peeked cert to check SQUID_X509_V_ERR_CERT_CHANGE
            if (X509 *peeked_cert = serverBump->serverCert.get()) {
                X509_up_ref(peeked_cert);
                SSL_set_ex_data(serverSession.get(), ssl_ex_index_ssl_peeked_cert, peeked_cert);
            }
        }
    }

    return true;
}