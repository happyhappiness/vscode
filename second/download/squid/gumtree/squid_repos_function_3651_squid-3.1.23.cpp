bool IpAddress::GetReverseString4(char buf[MAX_IPSTRLEN], const struct in_addr &dat) const
{
    unsigned int i = (unsigned int) ntohl(dat.s_addr);
    snprintf(buf, 32, "%u.%u.%u.%u.in-addr.arpa.",
             i & 255,
             (i >> 8) & 255,
             (i >> 16) & 255,
             (i >> 24) & 255);
    return true;
}