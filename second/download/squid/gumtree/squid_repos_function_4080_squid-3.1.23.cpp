static bool makeRequest(Ssl::X509_REQ_Pointer & request, Ssl::EVP_PKEY_Pointer const & pkey, char const * host)
{
    if (!X509_REQ_set_version(request.get(), 0L))
        return false;

    if (!addCnToRequest(request, host))
        return false;

    if (!X509_REQ_set_pubkey(request.get(), pkey.get()))
        return false;
    return true;
}