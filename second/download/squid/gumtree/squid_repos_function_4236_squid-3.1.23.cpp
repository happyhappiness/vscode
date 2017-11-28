void
ACLSslErrorData::parse()
{
    CbDataList<Ssl::ssl_error_t> **Tail;
    char *t = NULL;

    for (Tail = &values; *Tail; Tail = &((*Tail)->next));
    while ((t = strtokFile())) {
        CbDataList<Ssl::ssl_error_t> *q = new CbDataList<Ssl::ssl_error_t>(Ssl::parseErrorString(t));
        *(Tail) = q;
        Tail = &q->next;
    }
}