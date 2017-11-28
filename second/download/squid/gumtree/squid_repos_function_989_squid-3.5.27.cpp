void HttpMsg::packInto(Packer *p, bool full_uri) const
{
    packFirstLineInto(p, full_uri);
    header.packInto(p);
    packerAppend(p, "\r\n", 2);
}