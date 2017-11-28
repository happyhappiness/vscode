void
HttpReply::packInto(Packable * p) const
{
    packHeadersInto(p);
    body.packInto(p);
}