void
HttpReply::packHeadersInto(Packer * p) const
{
    sline.packInto(p);
    header.packInto(p);
    packerAppend(p, "\r\n", 2);
}