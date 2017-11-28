void
httpHdrContRangePackInto(const HttpHdrContRange * range, Packable * p)
{
    assert(range && p);
    httpHdrRangeRespSpecPackInto(&range->spec, p);
    /* Ensure typecast is safe */
    assert (range->elength >= 0);

    if (!known_spec(range->elength))
        p->append("/*", 2);
    else
        p->appendf("/%" PRId64, range->elength);
}