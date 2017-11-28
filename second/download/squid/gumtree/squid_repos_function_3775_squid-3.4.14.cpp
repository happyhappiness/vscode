bool
Ip::Address::operator <=(const Ip::Address &rhs) const
{
    if (isAnyAddr() && !rhs.isAnyAddr())
        return true;

    return (matchIPAddr(rhs) <= 0);
}