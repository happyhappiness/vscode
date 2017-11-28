void
ACLProtocolData::parse()
{
    CbDataList<protocol_t> **Tail;
    char *t = NULL;

    for (Tail = &values; *Tail; Tail = &((*Tail)->next));
    while ((t = strtokFile())) {
        CbDataList<protocol_t> *q = new CbDataList<protocol_t> (urlParseProtocol(t));
        *(Tail) = q;
        Tail = &q->next;
    }
}