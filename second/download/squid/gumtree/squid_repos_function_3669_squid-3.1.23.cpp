bool IpAddress::operator !=(const IpAddress &s) const
{
    return ! ( operator==(s) );
}