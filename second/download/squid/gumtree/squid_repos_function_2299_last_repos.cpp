ETag
HttpHeader::getETag(Http::HdrType id) const
{
    ETag etag = {NULL, -1};
    HttpHeaderEntry *e;
    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftETag);     /* must be of an appropriate type */

    if ((e = findEntry(id)))
        etagParseInit(&etag, e->value.termedBuf());

    return etag;
}