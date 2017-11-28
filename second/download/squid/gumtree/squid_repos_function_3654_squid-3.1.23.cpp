bool IpAddress::operator =(const char* s)
{
    return LookupHostIP(s, true);
}