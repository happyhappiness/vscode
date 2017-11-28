ACLSslErrorData *
ACLSslErrorData::clone() const
{
    return new ACLSslErrorData(*this);
}