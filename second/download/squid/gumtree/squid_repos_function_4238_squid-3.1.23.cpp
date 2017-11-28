ACLData<Ssl::ssl_error_t> *
ACLSslErrorData::clone() const
{
    /* Splay trees don't clone yet. */
    assert (!values);
    return new ACLSslErrorData(*this);
}