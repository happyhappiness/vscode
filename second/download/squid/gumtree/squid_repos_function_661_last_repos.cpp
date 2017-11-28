void HttpMsg::packInto(Packable *p, bool full_uri) const
{
    packFirstLineInto(p, full_uri);
    header.packInto(p);
    p->append("\r\n", 2);
}