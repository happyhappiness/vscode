int
ACLCertificateStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    const int fd = checklist->fd();
    const bool goodDescriptor = 0 <= fd && fd <= Biggest_FD;
    SSL *ssl = goodDescriptor ? fd_table[fd].ssl : 0;
    return data->match (ssl);
}