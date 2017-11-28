static int
aclArpCompare(acl_arp_data * const &a, acl_arp_data * const &b)
{
    return memcmp(a->eth, b->eth, 6);
}