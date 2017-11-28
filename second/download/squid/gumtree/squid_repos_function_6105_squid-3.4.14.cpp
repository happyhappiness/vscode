void
ESISegment::dumpOne() const
{
    String temp;
    temp.limitInit(buf, len);
    debugs(86, 9, "ESISegment::dumpOne: \"" << temp << "\"");
}