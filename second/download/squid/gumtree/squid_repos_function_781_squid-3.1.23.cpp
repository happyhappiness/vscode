void
HttpReply::packInto(Packer * p)
{
    packHeadersInto(p);
    httpBodyPackInto(&body, p);
}