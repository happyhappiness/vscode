bool
Ssl::CertError::operator == (const CertError &ce) const
{
    return code == ce.code && cert.get() == ce.cert.get();
}