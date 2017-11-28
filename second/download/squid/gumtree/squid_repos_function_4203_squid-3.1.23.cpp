static void
aclDumpArpListWalkee(acl_arp_data * const &node, void *state)
{
    acl_arp_data *arp = node;
    static char buf[24];
    snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
             arp->eth[0] & 0xff, arp->eth[1] & 0xff,
             arp->eth[2] & 0xff, arp->eth[3] & 0xff,
             arp->eth[4] & 0xff, arp->eth[5] & 0xff);
    wordlistAdd((wordlist **)state, buf);
}