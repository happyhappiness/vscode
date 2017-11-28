X509_REQ * Ssl::createNewX509Request(Ssl::EVP_PKEY_Pointer const & pkey, const char * hostname)
{
    Ssl::X509_REQ_Pointer request(X509_REQ_new());

    if (!request)
        return NULL;

    if (!makeRequest(request, pkey, hostname))
        return NULL;
    return request.release();
}