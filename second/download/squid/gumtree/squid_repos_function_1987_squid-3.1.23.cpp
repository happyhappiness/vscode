void
httpHdrContRangeSet(HttpHdrContRange * cr, HttpHdrRangeSpec spec, int64_t ent_len)
{
    assert(cr && ent_len >= 0);
    cr->spec = spec;
    cr->elength = ent_len;
}