static void
swap(struct hstruct *a, struct hstruct *b)
{
    struct hstruct c;

    c.host = a->host;
    c.priority = a->priority;
    c.weight = a->weight;
    a->host = b->host;
    a->priority = b->priority;
    a->weight = b->weight;
    b->host = c.host;
    b->priority = c.priority;
    b->weight = c.weight;
}