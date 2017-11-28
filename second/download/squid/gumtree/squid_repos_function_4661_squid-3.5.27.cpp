void
ACLMethodData::parse()
{
    CbDataList<HttpRequestMethod> **Tail;
    char *t = NULL;

    for (Tail = &values; *Tail; Tail = &((*Tail)->next));
    while ((t = strtokFile())) {
        CbDataList<HttpRequestMethod> *q = new CbDataList<HttpRequestMethod> (HttpRequestMethod(t, NULL));
        if (q->element == Http::METHOD_PURGE)
            ++ThePurgeCount; // configuration code wants to know
        *(Tail) = q;
        Tail = &q->next;
    }
}