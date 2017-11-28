HttpHdrContRange *
httpHdrContRangeDup(const HttpHdrContRange * range)
{
    HttpHdrContRange *dup;
    assert(range);
    dup = httpHdrContRangeCreate();
    *dup = *range;
    return dup;
}