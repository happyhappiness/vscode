ACLData<SSL *> *
ACLCertificateData::clone() const
{
    /* Splay trees don't clone yet. */
    return new ACLCertificateData(*this);
}