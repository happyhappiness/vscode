int
ACLServerCertificateStrategy::match(ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    Security::CertPointer cert;
    if (checklist->serverCert)
        cert = checklist->serverCert;
    else if (checklist->conn() != NULL && checklist->conn()->serverBump())
        cert = checklist->conn()->serverBump()->serverCert;

    if (!cert)
        return 0;

    return data->match(cert.get());
}