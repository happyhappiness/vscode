int
HttpHeaderEntry::getInt() const
{
    int val = -1;
    int ok = httpHeaderParseInt(value.termedBuf(), &val);
    httpHeaderNoteParsedEntry(id, value, ok == 0);
    /* XXX: Should we check ok - ie
     * return ok ? -1 : value;
     */
    return val;
}