void
HttpHdrRangeSpec::outputInfo( char const *note) const
{
    debugs(64, 5, "HttpHdrRangeSpec::canonize: " << note << ": [" <<
           offset << ", " << offset + length <<
           ") len: " << length);
}