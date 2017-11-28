int
ACLMaxConnection::match(ACLChecklist *checklist)
{
    return clientdbEstablished(Filled(checklist)->src_addr, 0) > limit ? 1 : 0;
}