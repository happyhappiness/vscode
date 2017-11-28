Ip::Address&
Ip::Address::operator =(const Ip::Address &s)
{
    memcpy(this, &s, sizeof(Ip::Address));
    return *this;
}