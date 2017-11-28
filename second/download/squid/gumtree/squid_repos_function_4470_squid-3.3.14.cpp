void
ACLSslErrorData::parse()
{
    Ssl::Errors **Tail;
    char *t = NULL;

    for (Tail = &values; *Tail; Tail = &((*Tail)->next));
    while ((t = strtokFile())) {
        Ssl::Errors *q = Ssl::ParseErrorString(t);
        *(Tail) = q;
        Tail = &q->tail()->next;
    }
}