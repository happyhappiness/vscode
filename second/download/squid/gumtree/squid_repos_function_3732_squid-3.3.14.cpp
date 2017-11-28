bool
Ip::Address::GetHostByName(const char* s)
{
    return LookupHostIP(s, false);
}