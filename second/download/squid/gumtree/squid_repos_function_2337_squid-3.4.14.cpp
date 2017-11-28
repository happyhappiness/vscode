void
httpHeaderAddContRange(HttpHeader * hdr, HttpHdrRangeSpec spec, int64_t ent_len)
{
    HttpHdrContRange *cr = httpHdrContRangeCreate();
    assert(hdr && ent_len >= 0);
    httpHdrContRangeSet(cr, spec, ent_len);
    hdr->putContRange(cr);
    httpHdrContRangeDestroy(cr);
}