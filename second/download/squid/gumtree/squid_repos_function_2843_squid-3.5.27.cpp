int64_t
HttpHeaderEntry::getInt64() const
{
    assert_eid (id);
    int64_t val = -1;
    int ok = httpHeaderParseOffset(value.termedBuf(), &val);
    httpHeaderNoteParsedEntry(id, value, !ok);
    /* XXX: Should we check ok - ie
     * return ok ? -1 : value;
     */
    return val;
}