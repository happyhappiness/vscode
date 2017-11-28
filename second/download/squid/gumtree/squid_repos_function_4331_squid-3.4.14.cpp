Ssl::CertValidationResponse::RecvdError & Ssl::CertValidationResponse::RecvdError::operator = (const RecvdError &old)
{
    id = old.id;
    error_no = old.error_no;
    error_reason = old.error_reason;
    setCert(old.cert.get());
    return *this;
}