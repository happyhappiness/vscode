int
HttpHdrRange::canonize(HttpReply *rep)
{
    assert(rep);

    if (rep->content_range)
        clen = rep->content_range->elength;
    else
        clen = rep->content_length;

    return canonize (clen);
}