int
rfc1035QueryCompare(const rfc1035_query * a, const rfc1035_query * b)
{
    size_t la, lb;
    if (a->qtype != b->qtype)
        return 1;
    if (a->qclass != b->qclass)
        return 1;
    la = strlen(a->name);
    lb = strlen(b->name);
    if (la != lb) {
        /* Trim root label(s) */
        while (la > 0 && a->name[la - 1] == '.')
            la--;
        while (lb > 0 && b->name[lb - 1] == '.')
            lb--;
    }
    if (la != lb)
        return 1;

    return strncasecmp(a->name, b->name, la);
}