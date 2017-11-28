HttpHdrContRange *
httpHdrContRangeCreate(void)
{
    HttpHdrContRange *r = (HttpHdrContRange *)memAllocate(MEM_HTTP_HDR_CONTENT_RANGE);
    r->spec.offset = r->spec.length = range_spec_unknown;
    r->elength = range_spec_unknown;
    return r;
}