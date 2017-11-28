bool IpAddress::GetHostByName(const char* s)
{
    return LookupHostIP(s, false);
}