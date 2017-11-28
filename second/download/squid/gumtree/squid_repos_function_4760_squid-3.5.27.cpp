void operator() (acl_ip_data * const & ip) {
        contents.push_back(ip->toSBuf());
    }