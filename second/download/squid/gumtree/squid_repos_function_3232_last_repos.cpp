int
Ip::Address::compareWhole(const Ip::Address &rhs) const
{
    return memcmp(this, &rhs, sizeof(*this));
}