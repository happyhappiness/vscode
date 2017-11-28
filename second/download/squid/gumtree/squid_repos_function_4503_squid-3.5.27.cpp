void
Ssl::CertValidationMsg::CertItem::setCert(X509 *aCert)
{
    cert.resetAndLock(aCert);
}