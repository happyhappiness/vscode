bool
Security::PeerConnector::initialize(Security::SessionPointer &serverSession)
{
    Security::ContextPointer ctx(getTlsContext());
    debugs(83, 5, serverConnection() << ", ctx=" << (void*)ctx.get());

    if (!ctx || !Security::CreateClientSession(ctx, serverConnection(), "server https start")) {
        const auto xerrno = errno;
        if (!ctx) {
            debugs(83, DBG_IMPORTANT, "Error initializing TLS connection: No security context.");
        } // else CreateClientSession() did the appropriate debugs() already
        ErrorState *anErr = new ErrorState(ERR_SOCKET_FAILURE, Http::scInternalServerError, request.getRaw());
        anErr->xerrno = xerrno;
        noteNegotiationDone(anErr);
        bail(anErr);
        return false;
    }

    // A TLS/SSL session has now been created for the connection and stored in fd_table
    serverSession = fd_table[serverConnection()->fd].ssl;
    debugs(83, 5, serverConnection() << ", session=" << (void*)serverSession.get());

#if USE_OPENSSL
    // If CertValidation Helper used do not lookup checklist for errors,
    // but keep a list of errors to send it to CertValidator
    if (!Ssl::TheConfig.ssl_crt_validator) {
        // Create the ACL check list now, while we have access to more info.
        // The list is used in ssl_verify_cb() and is freed in ssl_free().
        if (acl_access *acl = ::Config.ssl_client.cert_error) {
            ACLFilledChecklist *check = new ACLFilledChecklist(acl, request.getRaw(), dash_str);
            check->al = al;
            // check->fd(fd); XXX: need client FD here
            SSL_set_ex_data(serverSession.get(), ssl_ex_index_cert_error_check, check);
        }
    }
#endif

    return true;
}