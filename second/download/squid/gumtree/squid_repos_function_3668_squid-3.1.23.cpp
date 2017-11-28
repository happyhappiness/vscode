bool IpAddress::operator ==(const IpAddress &s) const
{
    return (0 == matchIPAddr(s));
}