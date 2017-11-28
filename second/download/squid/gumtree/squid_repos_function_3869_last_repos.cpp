::CertValidationResponse::RecvdError &
Ssl::CertValidationResponse::getError(int errorId)
{
    typedef Ssl::CertValidationResponse::RecvdErrors::iterator SVCREI;
    for (SVCREI i = errors.begin(); i != errors.end(); ++i) {
        if (i->id == errorId)
            return *i;
    }
    Ssl::CertValidationResponse::RecvdError errItem;
    errItem.id = errorId;
    errors.push_back(errItem);
    return errors.back();
}