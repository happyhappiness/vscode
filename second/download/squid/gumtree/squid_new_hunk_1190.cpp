            (validationResponse->resultCode == ::Helper::Okay || validationResponse->resultCode == ::Helper::Error)) {
        Ssl::CertValidationResponse::Pointer *item = new Ssl::CertValidationResponse::Pointer(validationResponse);
        if (!Ssl::CertValidationHelper::HelperCache->add(crtdvdData->query.c_str(), item))
            delete item;
    }

    delete crtdvdData;
}

void Ssl::CertValidationHelper::sslSubmit(Ssl::CertValidationRequest const &request, AsyncCall::Pointer &callback)
{
    assert(ssl_crt_validator);

    Ssl::CertValidationMsg message(Ssl::CrtdMessage::REQUEST);
    message.setCode(Ssl::CertValidationMsg::code_cert_validate);
    message.composeRequest(request);
    debugs(83, 5, "SSL crtvd request: " << message.compose().c_str());

    submitData *crtdvdData = new submitData;
    crtdvdData->query = message.compose();
    crtdvdData->query += '\n';
    crtdvdData->callback = callback;
    crtdvdData->ssl = request.ssl;
    Ssl::CertValidationResponse::Pointer const*validationResponse;

    if (CertValidationHelper::HelperCache &&
            (validationResponse = CertValidationHelper::HelperCache->get(crtdvdData->query.c_str()))) {

        CertValidationHelper::CbDialer *dialer = dynamic_cast<CertValidationHelper::CbDialer*>(callback->getDialer());
        Must(dialer);
        dialer->arg1 = *validationResponse;
        ScheduleCallHere(callback);
        delete crtdvdData;
        return;
    }

    if (!ssl_crt_validator->trySubmit(crtdvdData->query.c_str(), sslCrtvdHandleReplyWrapper, crtdvdData)) {
        Ssl::CertValidationResponse::Pointer resp = new Ssl::CertValidationResponse;;
        resp->resultCode = ::Helper::BrokenHelper;
        Ssl::CertValidationHelper::CbDialer *dialer = dynamic_cast<Ssl::CertValidationHelper::CbDialer*>(callback->getDialer());
        Must(dialer);
        dialer->arg1 = resp;
        ScheduleCallHere(callback);
        delete crtdvdData;
        return;
    }
}

