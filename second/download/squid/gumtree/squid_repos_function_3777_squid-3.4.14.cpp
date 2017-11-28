bool
Ip::Address::operator >(const Ip::Address &rhs) const
{
    if (isNoAddr() && !rhs.isNoAddr())
        return true;

    return ( matchIPAddr(rhs) > 0);
}