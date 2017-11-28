bool
Ip::Address::operator >(const Ip::Address &rhs) const
{
    if (IsNoAddr() && !rhs.IsNoAddr())
        return true;

    return ( matchIPAddr(rhs) > 0);
}