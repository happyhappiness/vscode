bool

ACLASN::match(Ip::Address toMatch)
{
    return asnMatchIp(data, toMatch);
}