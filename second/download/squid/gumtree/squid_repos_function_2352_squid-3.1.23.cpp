void
ipcacheMergeIPLists(const IpAddress *aaddrs, const int alen,
                    const IpAddress *baddrs, const int blen,
                    IpAddress **out, int &outlen )
{
    int fc=0, t=0, c=0;

    IpAddress const *ip4ptrs[255];
    IpAddress const *ip6ptrs[255];
    int num_ip4 = 0;
    int num_ip6 = 0;

    memset(ip4ptrs, 0, sizeof(IpAddress*)*255);
    memset(ip6ptrs, 0, sizeof(IpAddress*)*255);

    // for each unique address in list A - grab ptr
    for (t = 0; t < alen; t++) {
        if (aaddrs[t].IsIPv4()) {
            // check against IPv4 pruned list
            for (c = 0; c <= num_ip4; c++) {
                if (ip4ptrs[c] && aaddrs[t] == *(ip4ptrs[c]) ) break; // duplicate.
            }
            if (c > num_ip4) {
                ip4ptrs[num_ip4] = &aaddrs[t];
                num_ip4++;
            }
        } else if (aaddrs[t].IsIPv6()) {
            debugs(14,8, HERE << "A[" << t << "]=IPv6 " << aaddrs[t]);
            // check against IPv6 pruned list
            for (c = 0; c <= num_ip6; c++) {
                if (ip6ptrs[c] && aaddrs[t] == *ip6ptrs[c]) break; // duplicate.
            }
            if (c > num_ip6) {
                ip6ptrs[num_ip6] = &aaddrs[t];
                num_ip6++;
            }
        }
    }

    // for each unique address in list B - grab ptr
    for (t = 0; t < blen; t++) {
        if (baddrs[t].IsIPv4()) {
            // check against IPv4 pruned list
            for (c = 0; c <= num_ip4; c++) {
                if (ip4ptrs[c] && baddrs[t] == *ip4ptrs[c]) break; // duplicate.
            }
            if (c > num_ip4) {
                ip4ptrs[num_ip4] = &baddrs[t];
                num_ip4++;
            }
        } else if (baddrs[t].IsIPv6()) {
            // check against IPv6 pruned list
            for (c = 0; c <= num_ip6; c++) {
                if (ip6ptrs[c] && baddrs[t] == *ip6ptrs[c]) break; // duplicate.
            }
            if (c > num_ip6) {
                ip6ptrs[num_ip6] = &baddrs[t];
                num_ip6++;
            }
        }
    }

    fc = num_ip6 + num_ip4;

    assert(fc > 0);

    debugs(14, 5, "ipcacheMergeIPLists: Merge " << alen << "+" << blen << " into " << fc << " unique IPs.");

    // copy the old IPs into the new list buffer.
    (*out) = (IpAddress*)xcalloc(fc, sizeof(IpAddress));
    outlen=0;

    assert(out != NULL);

    /* IPv6 are preferred (tried first) over IPv4 */

    for (int l = 0; outlen < num_ip6; l++, outlen++) {
        (*out)[outlen] = *ip6ptrs[l];
        debugs(14, 5, "ipcacheMergeIPLists:  #" << outlen << " " << (*out)[outlen] );
    }

    for (int l = 0; outlen < num_ip4; l++, outlen++) {
        (*out)[outlen] = *ip4ptrs[l];
        debugs(14, 5, "ipcacheMergeIPLists:  #" << outlen << " " << (*out)[outlen] );
    }

    assert(outlen == fc); // otherwise something broke badly!
}