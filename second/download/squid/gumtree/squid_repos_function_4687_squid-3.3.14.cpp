void
ACLProtocolData::parse()
{
    CbDataList<AnyP::ProtocolType> **Tail;
    char *t = NULL;

    for (Tail = &values; *Tail; Tail = &((*Tail)->next));
    while ((t = strtokFile())) {
        int p = AnyP::PROTO_NONE;
        for (; p < AnyP::PROTO_UNKNOWN; ++p) {
            if (strcasecmp(t, AnyP::ProtocolType_str[p]) == 0) {
                CbDataList<AnyP::ProtocolType> *q = new CbDataList<AnyP::ProtocolType>(static_cast<AnyP::ProtocolType>(p));
                *(Tail) = q;
                Tail = &q->next;
                break;
            }
        }
        if (p == AnyP::PROTO_UNKNOWN) {
            debugs(28, DBG_IMPORTANT, "WARNING: Ignoring unknown protocol '" << t << "' in the ACL named '" << AclMatchedName << "'");
            // XXX: store the text pattern of this protocol name for live comparisons
        }
    }
}