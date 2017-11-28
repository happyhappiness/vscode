bool IpAddress::operator >=(const IpAddress &rhs) const
{
    if (IsNoAddr() && !rhs.IsNoAddr())
        return true;

    return ( matchIPAddr(rhs) >= 0);
}