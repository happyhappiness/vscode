X509 *
findCertByIssuerFast(X509_STORE_CTX *ctx, Ssl::CertsIndexedList &list, X509 *cert)
{
    static char buffer[2048];

    if (X509_NAME *issuerName = X509_get_issuer_name(cert))
        X509_NAME_oneline(issuerName, buffer, sizeof(buffer));
    else
        return NULL;

    typedef std::pair<Ssl::CertsIndexedList::iterator, Ssl::CertsIndexedList::iterator> Pair;
    const Pair ret = list.equal_range(SBuf(buffer));
    for (Ssl::CertsIndexedList::iterator it = ret.first; it != ret.second; ++it) {
        X509 *issuer = it->second;
        if (ctx->check_issued(ctx, cert, issuer)) {
            return issuer;
        }
    }
    return NULL;
}