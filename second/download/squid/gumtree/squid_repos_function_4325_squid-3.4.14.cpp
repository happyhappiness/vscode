Ssl::CertError &
Ssl::CertError::operator = (const CertError &old)
{
    code = old.code;
    cert.resetAndLock(old.cert.get());
    return *this;
}