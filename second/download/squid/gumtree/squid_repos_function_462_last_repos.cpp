void
HttpReply::packHeadersInto(Packable * p) const
{
    sline.packInto(p);
    header.packInto(p);
    p->append("\r\n", 2);
}