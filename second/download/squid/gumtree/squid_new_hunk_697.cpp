int
ACLMaxConnection::match(ACLChecklist *checklist)
{
    return clientdbEstablished(Filled(checklist)->src_addr, 0) > limit ? 1 : 0;
}

SBufList
ACLMaxConnection::dump() const
{
    SBufList sl;
    if (!limit)
        return sl;

    SBuf s;
    s.Printf("%d", limit);
    sl.push_back(s);
    return sl;
}

void
ACLMaxConnection::prepareForUse()
{
    if (0 != Config.onoff.client_db)
