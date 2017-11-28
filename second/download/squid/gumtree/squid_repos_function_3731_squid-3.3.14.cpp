bool
Ip::Address::operator =(const char* s)
{
    return LookupHostIP(s, true);
}