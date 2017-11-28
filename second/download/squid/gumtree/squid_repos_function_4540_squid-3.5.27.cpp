static void
sslCrtvdHandleReplyWrapper(void *data, const ::Helper::Reply &reply)
{
    Ssl::CertValidationMsg replyMsg(Ssl::CrtdMessage::REPLY);
    Ssl::CertValidationResponse::Pointer validationResponse = new Ssl::CertValidationResponse;
    std::string error;

    submitData *crtdvdData = static_cast<submitData *>(data);
    STACK_OF(X509) *peerCerts = SSL_get_peer_cert_chain(crtdvdData->ssl);
    if (reply.result == ::Helper::BrokenHelper) {
        debugs(83, DBG_IMPORTANT, "\"ssl_crtvd\" helper error response: " << reply.other().content());
        validationResponse->resultCode = ::Helper::BrokenHelper;
    } else if (replyMsg.parse(reply.other().content(), reply.other().contentSize()) != Ssl::CrtdMessage::OK ||
               !replyMsg.parseResponse(*validationResponse, peerCerts, error) ) {
        debugs(83, DBG_IMPORTANT, "WARNING: Reply from ssl_crtvd for " << " is incorrect");
        debugs(83, DBG_IMPORTANT, "Certificate cannot be validated. ssl_crtvd response: " << replyMsg.getBody());
        validationResponse->resultCode = ::Helper::BrokenHelper;
    } else
        validationResponse->resultCode = reply.result;

    Ssl::CertValidationHelper::CbDialer *dialer = dynamic_cast<Ssl::CertValidationHelper::CbDialer*>(crtdvdData->callback->getDialer());
    Must(dialer);
    dialer->arg1 = validationResponse;
    ScheduleCallHere(crtdvdData->callback);

    if (Ssl::CertValidationHelper::HelperCache &&
            (validationResponse->resultCode == ::Helper::Okay || validationResponse->resultCode == ::Helper::Error)) {
        Ssl::CertValidationResponse::Pointer *item = new Ssl::CertValidationResponse::Pointer(validationResponse);
        if (!Ssl::CertValidationHelper::HelperCache->add(crtdvdData->query.c_str(), item))
            delete item;
    }

    SSL_free(crtdvdData->ssl);
    delete crtdvdData;
}