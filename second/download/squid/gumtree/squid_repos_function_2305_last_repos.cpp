int64_t
HttpHeaderEntry::getInt64() const
{
    int64_t val = -1;
    const bool ok = httpHeaderParseOffset(value.termedBuf(), &val);
    httpHeaderNoteParsedEntry(id, value, !ok);
    return val; // remains -1 if !ok (XXX: bad method API)
}