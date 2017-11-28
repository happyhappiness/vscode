bool
Ip::Address::operator ==(const Ip::Address &s) const
{
    return (0 == matchIPAddr(s));
}