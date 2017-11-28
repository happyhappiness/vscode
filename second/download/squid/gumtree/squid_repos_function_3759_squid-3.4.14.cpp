bool
Ip::Address::GetHostByName(const char* s)
{
    return lookupHostIP(s, false);
}