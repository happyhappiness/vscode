int
ACLCertificateStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    const int fd = checklist->fd();
    const bool goodDescriptor = 0 <= fd && fd <= Biggest_FD;
    SSL *ssl = goodDescriptor ? fd_table[fd].ssl : 0;
    X509 *cert = SSL_get_peer_certificate(ssl);
    const bool res = data->match (cert);
    X509_free(cert);
    return res;
}