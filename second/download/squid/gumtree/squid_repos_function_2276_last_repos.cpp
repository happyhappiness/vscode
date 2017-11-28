int
HttpHeader::has(Http::HdrType id) const
{
    assert(any_registered_header(id));
    debugs(55, 9, this << " lookup for " << id);
    return CBIT_TEST(mask, id);
}