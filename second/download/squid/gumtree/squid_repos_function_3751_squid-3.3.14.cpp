bool
Ip::Address::operator <(const Ip::Address &rhs) const
{
    if (IsAnyAddr() && !rhs.IsAnyAddr())
        return true;

    return ( matchIPAddr(rhs) < 0);
}