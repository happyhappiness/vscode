size_t
ESISegment::space() const
{
    assert (len <= sizeof(buf));
    return sizeof (buf) - len;
}