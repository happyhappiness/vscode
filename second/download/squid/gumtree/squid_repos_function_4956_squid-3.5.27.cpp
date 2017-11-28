int
ACLServerCertificateStrategy::match(ACLData<MatchType> * &data, ACLFilledChecklist *checklist, ACLFlags &)
{
    X509 *cert = NULL;
    if (checklist->serverCert.get())
        cert = checklist->serverCert.get();
    else if (checklist->conn() != NULL && checklist->conn()->serverBump())
        cert = checklist->conn()->serverBump()->serverCert.get();

    if (!cert)
        return 0;

    return data->match(cert);
}