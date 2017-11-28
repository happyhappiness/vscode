void
Ssl::PeerConnector::sslCrtvdHandleReply(Ssl::CertValidationResponse::Pointer validationResponse)
{
    Must(validationResponse != NULL);

    Ssl::ErrorDetail *errDetails = NULL;
    bool validatorFailed = false;
    if (!Comm::IsConnOpen(serverConnection())) {
        return;
    }

    debugs(83,5, request->GetHost() << " cert validation result: " << validationResponse->resultCode);

    if (validationResponse->resultCode == ::Helper::Error) {
        if (Ssl::CertErrors *errs = sslCrtvdCheckForErrors(*validationResponse, errDetails)) {
            SSL *ssl = fd_table[serverConnection()->fd].ssl;
            Ssl::CertErrors *oldErrs = static_cast<Ssl::CertErrors*>(SSL_get_ex_data(ssl, ssl_ex_index_ssl_errors));
            SSL_set_ex_data(ssl, ssl_ex_index_ssl_errors,  (void *)errs);
            delete oldErrs;
        }
    } else if (validationResponse->resultCode != ::Helper::Okay)
        validatorFailed = true;

    if (!errDetails && !validatorFailed) {
        serverCertificateVerified();
        if (splice)
            switchToTunnel(request.getRaw(), clientConn, serverConn);
        else
            callBack();
        return;
    }

    ErrorState *anErr = NULL;
    if (validatorFailed) {
        anErr = new ErrorState(ERR_GATEWAY_FAILURE, Http::scInternalServerError, request.getRaw());
    }  else {
        anErr =  new ErrorState(ERR_SECURE_CONNECT_FAIL, Http::scServiceUnavailable, request.getRaw());
        anErr->detail = errDetails;
        /*anErr->xerrno= Should preserved*/
    }

    bail(anErr);
    if (serverConnection()->getPeer()) {
        peerConnectFailed(serverConnection()->getPeer());
    }
    serverConn->close();
    return;
}