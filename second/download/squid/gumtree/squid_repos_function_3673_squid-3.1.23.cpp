bool IpAddress::operator <(const IpAddress &rhs) const
{
    if (IsAnyAddr() && !rhs.IsAnyAddr())
        return true;

    return ( matchIPAddr(rhs) < 0);
}