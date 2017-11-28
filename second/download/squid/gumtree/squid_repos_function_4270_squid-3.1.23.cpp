int
acl_ip_data::NetworkCompare(acl_ip_data * const & a, acl_ip_data * const &b)
{
    int ret;
    bool bina = true;
    ret = aclIpAddrNetworkCompare(b, a);

    if (ret != 0) {
        bina = false;
        ret = aclIpAddrNetworkCompare(a, b);
    }

    if (ret == 0) {
        char buf_n1[3*(MAX_IPSTRLEN+1)];
        char buf_n2[3*(MAX_IPSTRLEN+1)];
        if (bina) {
            b->toStr(buf_n1, 3*(MAX_IPSTRLEN+1));
            a->toStr(buf_n2, 3*(MAX_IPSTRLEN+1));
        } else {
            a->toStr(buf_n1, 3*(MAX_IPSTRLEN+1));
            b->toStr(buf_n2, 3*(MAX_IPSTRLEN+1));
        }
        debugs(28, 0, "WARNING: (" << (bina?'B':'A') << ") '" << buf_n1 << "' is a subnetwork of (" << (bina?'A':'B') << ") '" << buf_n2 << "'");
        debugs(28, 0, "WARNING: because of this '" << (bina?buf_n2:buf_n1) << "' is ignored to keep splay tree searching predictable");
        debugs(28, 0, "WARNING: You should probably remove '" << buf_n1 << "' from the ACL named '" << AclMatchedName << "'");
    }

    return ret;
}