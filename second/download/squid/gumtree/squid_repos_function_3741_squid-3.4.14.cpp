bool
Ip::Address::isSockAddr() const
{
    return (mSocketAddr_.sin6_port != 0);
}