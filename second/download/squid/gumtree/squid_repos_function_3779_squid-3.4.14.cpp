unsigned short
Ip::Address::port() const
{
    return ntohs( mSocketAddr_.sin6_port );
}