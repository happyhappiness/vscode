int
ACLCertificateStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    const int fd = checklist->fd();
    const bool goodDescriptor = 0 <= fd && fd <= Biggest_FD;
    auto ssl = goodDescriptor ? fd_table[fd].ssl.get() : nullptr;
    X509 *cert = SSL_get_peer_certificate(ssl);
    const bool res = data->match (cert);
    X509_free(cert);
    return res;
}