int
ACLIP::match(const Ip::Address &clientip)
{
    static acl_ip_data ClientAddress;
    /*
     * aclIpAddrNetworkCompare() takes two acl_ip_data pointers as
     * arguments, so we must create a fake one for the client's IP
     * address. Since we are scanning for a single IP mask and addr2
     * MUST be set to empty.
     */
    ClientAddress.addr1 = clientip;
    ClientAddress.addr2.setEmpty();
    ClientAddress.mask.setEmpty();

    const acl_ip_data * const * result =  data->find(&ClientAddress, aclIpAddrNetworkCompare);
    debugs(28, 3, "aclIpMatchIp: '" << clientip << "' " << (result ? "found" : "NOT found"));
    return (result != NULL);
}