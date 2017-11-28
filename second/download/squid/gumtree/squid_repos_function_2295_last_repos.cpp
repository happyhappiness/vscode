HttpHdrRange *
HttpHeader::getRange() const
{
    HttpHdrRange *r = NULL;
    HttpHeaderEntry *e;
    /* some clients will send "Request-Range" _and_ *matching* "Range"
     * who knows, some clients might send Request-Range only;
     * this "if" should work correctly in both cases;
     * hopefully no clients send mismatched headers! */

    if ((e = findEntry(Http::HdrType::RANGE)) ||
            (e = findEntry(Http::HdrType::REQUEST_RANGE))) {
        r = HttpHdrRange::ParseCreate(&e->value);
        httpHeaderNoteParsedEntry(e->id, e->value, !r);
    }

    return r;
}