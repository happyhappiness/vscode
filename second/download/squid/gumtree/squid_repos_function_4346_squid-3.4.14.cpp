static void
sslCrtvdHandleReplyWrapper(void *data, const HelperReply &reply)
{
    Ssl::CertValidationMsg replyMsg(Ssl::CrtdMessage::REPLY);
    Ssl::CertValidationResponse *validationResponse = new Ssl::CertValidationResponse;
    std::string error;

    submitData *crtdvdData = static_cast<submitData *>(data);
    STACK_OF(X509) *peerCerts = SSL_get_peer_cert_chain(crtdvdData->ssl);
    if (reply.result == HelperReply::BrokenHelper) {
        debugs(83, DBG_IMPORTANT, "\"ssl_crtvd\" helper error response: " << reply.other().content());
        validationResponse->resultCode = HelperReply::BrokenHelper;
    } else if (replyMsg.parse(reply.other().content(), reply.other().contentSize()) != Ssl::CrtdMessage::OK ||
               !replyMsg.parseResponse(*validationResponse, peerCerts, error) ) {
        debugs(83, DBG_IMPORTANT, "WARNING: Reply from ssl_crtvd for " << " is incorrect");
        debugs(83, DBG_IMPORTANT, "Certificate cannot be validated. ssl_crtvd response: " << replyMsg.getBody());
        validationResponse->resultCode = HelperReply::BrokenHelper;
    } else
        validationResponse->resultCode = reply.result;

    crtdvdData->callback(crtdvdData->data, *validationResponse);

    if (Ssl::CertValidationHelper::HelperCache &&
            (validationResponse->resultCode == HelperReply::Okay || validationResponse->resultCode == HelperReply::Error)) {
        Ssl::CertValidationHelper::HelperCache->add(crtdvdData->query.c_str(), validationResponse);
    } else
        delete validationResponse;

    cbdataReferenceDone(crtdvdData->data);
    SSL_free(crtdvdData->ssl);
    delete crtdvdData;
}