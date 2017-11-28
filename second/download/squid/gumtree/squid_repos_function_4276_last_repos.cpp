void
ACLASN::parse()
{
    CbDataList<int> **curlist = &data;
    CbDataList<int> **Tail;
    CbDataList<int> *q = NULL;
    char *t = NULL;

    for (Tail = curlist; *Tail; Tail = &((*Tail)->next));
    while ((t = ConfigParser::strtokFile())) {
        q = new CbDataList<int> (atoi(t));
        *(Tail) = q;
        Tail = &q->next;
    }
}