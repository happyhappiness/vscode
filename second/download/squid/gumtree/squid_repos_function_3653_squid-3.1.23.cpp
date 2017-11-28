IpAddress& IpAddress::operator =(const IpAddress &s)
{
    memcpy(this, &s, sizeof(IpAddress));
    return *this;
}