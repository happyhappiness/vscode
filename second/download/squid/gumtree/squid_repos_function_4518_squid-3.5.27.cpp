bool
Ssl::PeerConnector::sslFinalized()
{
    const int fd = serverConnection()->fd;
    SSL *ssl = fd_table[fd].ssl;

    // In the case the session is resuming, the certificates does not exist and
    // we did not do any cert validation
    if (resumingSession)
        return true;

    handleServerCertificate();

    if (Ssl::TheConfig.ssl_crt_validator) {
        Ssl::CertValidationRequest validationRequest;
        // WARNING: Currently we do not use any locking for any of the
        // members of the Ssl::CertValidationRequest class. In this code the
        // Ssl::CertValidationRequest object used only to pass data to
        // Ssl::CertValidationHelper::submit method.
        validationRequest.ssl = ssl;
        validationRequest.domainName = request->GetHost();
        if (Ssl::CertErrors *errs = static_cast<Ssl::CertErrors *>(SSL_get_ex_data(ssl, ssl_ex_index_ssl_errors)))
            // validationRequest disappears on return so no need to cbdataReference
            validationRequest.errors = errs;
        else
            validationRequest.errors = NULL;
        try {
            debugs(83, 5, "Sending SSL certificate for validation to ssl_crtvd.");
            AsyncCall::Pointer call = asyncCall(83,5, "Ssl::PeerConnector::sslCrtvdHandleReply", Ssl::CertValidationHelper::CbDialer(this, &Ssl::PeerConnector::sslCrtvdHandleReply, NULL));
            Ssl::CertValidationHelper::GetInstance()->sslSubmit(validationRequest, call);
            return false;
        } catch (const std::exception &e) {
            debugs(83, DBG_IMPORTANT, "ERROR: Failed to compose ssl_crtvd " <<
                   "request for " << validationRequest.domainName <<
                   " certificate: " << e.what() << "; will now block to " <<
                   "validate that certificate.");
            // fall through to do blocking in-process generation.
            ErrorState *anErr = new ErrorState(ERR_GATEWAY_FAILURE, Http::scInternalServerError, request.getRaw());
            bail(anErr);
            if (serverConnection()->getPeer()) {
                peerConnectFailed(serverConnection()->getPeer());
            }
            serverConn->close();
            return true;
        }
    }

    serverCertificateVerified();
    return true;
}