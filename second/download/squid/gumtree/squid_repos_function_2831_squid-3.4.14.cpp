void
HttpHeaderEntry::packInto(Packer * p) const
{
    assert(p);
    packerAppend(p, name.rawBuf(), name.size());
    packerAppend(p, ": ", 2);
    packerAppend(p, value.rawBuf(), value.size());
    packerAppend(p, "\r\n", 2);
}