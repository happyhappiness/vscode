bool

ACLASN::match(IpAddress toMatch)
{
    return asnMatchIp(data, toMatch);
}