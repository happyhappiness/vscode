ETag
HttpHeader::getETag(http_hdr_type id) const
{
    ETag etag = {NULL, -1};
    HttpHeaderEntry *e;
    assert(Headers[id].type == ftETag);		/* must be of an appropriate type */

    if ((e = findEntry(id)))
        etagParseInit(&etag, e->value.termedBuf());

    return etag;
}