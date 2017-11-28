void Ssl::CertValidationHelper::sslSubmit(Ssl::CertValidationRequest const &request, AsyncCall::Pointer &callback)
{
    static time_t first_warn = 0;
    assert(ssl_crt_validator);

    if (ssl_crt_validator->stats.queue_size >= (int)(ssl_crt_validator->childs.n_running * 2)) {
        if (first_warn == 0)
            first_warn = squid_curtime;
        if (squid_curtime - first_warn > 3 * 60)
            fatal("ssl_crtvd queue being overloaded for long time");
        debugs(83, DBG_IMPORTANT, "WARNING: ssl_crtvd queue overload, rejecting");
        Ssl::CertValidationResponse::Pointer resp = new Ssl::CertValidationResponse;
        resp->resultCode = ::Helper::BrokenHelper;
        Ssl::CertValidationHelper::CbDialer *dialer = dynamic_cast<Ssl::CertValidationHelper::CbDialer*>(callback->getDialer());
        Must(dialer);
        dialer->arg1 = resp;
        ScheduleCallHere(callback);
        return;
    }
    first_warn = 0;

    Ssl::CertValidationMsg message(Ssl::CrtdMessage::REQUEST);
    message.setCode(Ssl::CertValidationMsg::code_cert_validate);
    message.composeRequest(request);
    debugs(83, 5, "SSL crtvd request: " << message.compose().c_str());

    submitData *crtdvdData = new submitData;
    crtdvdData->query = message.compose();
    crtdvdData->query += '\n';
    crtdvdData->callback = callback;
    crtdvdData->ssl = request.ssl;
    CRYPTO_add(&crtdvdData->ssl->references,1,CRYPTO_LOCK_SSL);
    Ssl::CertValidationResponse::Pointer const*validationResponse;

    if (CertValidationHelper::HelperCache &&
            (validationResponse = CertValidationHelper::HelperCache->get(crtdvdData->query.c_str()))) {

        CertValidationHelper::CbDialer *dialer = dynamic_cast<CertValidationHelper::CbDialer*>(callback->getDialer());
        Must(dialer);
        dialer->arg1 = *validationResponse;
        ScheduleCallHere(callback);
        SSL_free(crtdvdData->ssl);
        delete crtdvdData;
        return;
    }
    helperSubmit(ssl_crt_validator, crtdvdData->query.c_str(), sslCrtvdHandleReplyWrapper, crtdvdData);
}