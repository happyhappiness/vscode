bool
Ip::Address::operator !=(const Ip::Address &s) const
{
    return ! ( operator==(s) );
}