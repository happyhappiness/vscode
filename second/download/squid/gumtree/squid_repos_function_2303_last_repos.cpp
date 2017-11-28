void
HttpHeaderEntry::packInto(Packable * p) const
{
    assert(p);
    p->append(name.rawBuf(), name.size());
    p->append(": ", 2);
    p->append(value.rawBuf(), value.size());
    p->append("\r\n", 2);
}