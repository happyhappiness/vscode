void
HttpReply::packInto(Packer * p)
{
    packHeadersInto(p);
    body.packInto(p);
}