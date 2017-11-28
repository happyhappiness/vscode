bool
Ip::Address::operator =(const char* s)
{
    return lookupHostIP(s, true);
}