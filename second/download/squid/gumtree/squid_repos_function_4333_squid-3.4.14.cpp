Ssl::CertValidationMsg::CertItem & Ssl::CertValidationMsg::CertItem::operator = (const CertItem &old)
{
    name = old.name;
    setCert(old.cert.get());
    return *this;
}