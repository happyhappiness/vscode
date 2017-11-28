int
HttpHeaderEntry::getInt() const
{
    assert_eid (id);
    assert (Headers[id].type == ftInt);
    int val = -1;
    int ok = httpHeaderParseInt(value.termedBuf(), &val);
    httpHeaderNoteParsedEntry(id, value, !ok);
    /* XXX: Should we check ok - ie
     * return ok ? -1 : value;
     */
    return val;
}