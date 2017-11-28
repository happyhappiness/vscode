HttpHdrCc *
httpHdrCcDup(const HttpHdrCc * cc)
{
    HttpHdrCc *dup;
    assert(cc);
    dup = httpHdrCcCreate();
    dup->mask = cc->mask;
    dup->max_age = cc->max_age;
    dup->s_maxage = cc->s_maxage;
    dup->max_stale = cc->max_stale;
    dup->min_fresh = cc->min_fresh;
    return dup;
}