void
ACLMethodData::parse()
{
    CbDataList<HttpRequestMethod> **Tail;
    char *t = NULL;

    for (Tail = &values; *Tail; Tail = &((*Tail)->next));
    while ((t = strtokFile())) {
        if (strcmp(t, "PURGE") == 0)
            ++ThePurgeCount; // configuration code wants to know
        CbDataList<HttpRequestMethod> *q = new CbDataList<HttpRequestMethod> (HttpRequestMethod(t, NULL));
        *(Tail) = q;
        Tail = &q->next;
    }
}