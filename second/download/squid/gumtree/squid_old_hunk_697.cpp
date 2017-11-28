int
ACLMaxConnection::match(ACLChecklist *checklist)
{
    return clientdbEstablished(Filled(checklist)->src_addr, 0) > limit ? 1 : 0;
}

wordlist *
ACLMaxConnection::dump() const
{
    if (!limit)
        return NULL;

    wordlist *W = NULL;

    char buf[32];

    snprintf(buf, sizeof(buf), "%d", limit);

    wordlistAdd(&W, buf);

    return W;
}

void
ACLMaxConnection::prepareForUse()
{
    if (0 != Config.onoff.client_db)
