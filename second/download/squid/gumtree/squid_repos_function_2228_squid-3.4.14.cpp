void
FwdState::sslCrtvdHandleReply(Ssl::CertValidationResponse const &validationResponse)
{
    Ssl::CertErrors *errs = NULL;
    Ssl::ErrorDetail *errDetails = NULL;
    bool validatorFailed = false;
    if (!Comm::IsConnOpen(serverConnection())) {
        return;
    }

    debugs(83,5, request->GetHost() << " cert validation result: " << validationResponse.resultCode);

    if (validationResponse.resultCode == HelperReply::Error)
        errs = sslCrtvdCheckForErrors(validationResponse, errDetails);
    else if (validationResponse.resultCode != HelperReply::Okay)
        validatorFailed = true;

    if (!errDetails && !validatorFailed) {
        dispatch();
        return;
    }

    ErrorState *anErr = NULL;
    if (validatorFailed) {
        anErr = new ErrorState(ERR_GATEWAY_FAILURE, Http::scInternalServerError, request);
    }  else {

        // Check the list error with
        if (errDetails && request->clientConnectionManager.valid()) {
            // remember the server certificate from the ErrorDetail object
            if (Ssl::ServerBump *serverBump = request->clientConnectionManager->serverBump()) {
                // remember validation errors, if any
                if (errs) {
                    if (serverBump->sslErrors)
                        cbdataReferenceDone(serverBump->sslErrors);
                    serverBump->sslErrors = cbdataReference(errs);
                }
            }
        }

        anErr = makeConnectingError(ERR_SECURE_CONNECT_FAIL);
        anErr->detail = errDetails;
        /*anErr->xerrno= Should preserved*/
    }

    fail(anErr);
    if (serverConnection()->getPeer()) {
        peerConnectFailed(serverConnection()->getPeer());
    }
    serverConn->close();
    self = NULL;
    return;
}