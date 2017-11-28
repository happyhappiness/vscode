HttpHdrCc *
httpHdrCcCreate(void)
{
    HttpHdrCc *cc = (HttpHdrCc *)memAllocate(MEM_HTTP_HDR_CC);
    cc->max_age = cc->s_maxage = cc->max_stale = cc->min_fresh = -1;
    return cc;
}