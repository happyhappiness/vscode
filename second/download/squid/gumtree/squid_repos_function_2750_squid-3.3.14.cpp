String
HttpHeader::getStrOrList(http_hdr_type id) const
{
    HttpHeaderEntry *e;

    if (CBIT_TEST(ListHeadersMask, id))
        return getList(id);

    if ((e = findEntry(id)))
        return e->value;

    return String();
}