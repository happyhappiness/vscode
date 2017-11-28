void
httpHdrContRangePackInto(const HttpHdrContRange * range, Packer * p)
{
    assert(range && p);
    httpHdrRangeRespSpecPackInto(&range->spec, p);
    /* Ensure typecast is safe */
    assert (range->elength >= 0);

    if (!known_spec(range->elength))
        packerPrintf(p, "/*");
    else
        packerPrintf(p, "/%" PRId64, range->elength);
}