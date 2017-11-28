void HttpReply::packFirstLineInto(Packer *p, bool unused) const
{
    httpStatusLinePackInto(&sline, p);
}