HttpHeaderEntry *
HttpHeaderEntry::clone() const
{
    return new HttpHeaderEntry(id, name.termedBuf(), value.termedBuf());
}