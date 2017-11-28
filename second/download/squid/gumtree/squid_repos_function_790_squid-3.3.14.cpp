void
HttpReply::packHeadersInto(Packer * p) const
{
    httpStatusLinePackInto(&sline, p);
    header.packInto(p);
    packerAppend(p, "\r\n", 2);
}