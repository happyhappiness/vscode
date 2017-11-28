void
Ssl::CertValidationResponse::RecvdError::setCert(X509 *aCert)
{
    cert.resetAndLock(aCert);
}