int
ACLARP::match(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);

    /* IPv6 does not do ARP */
    if (!checklist->src_addr.IsIPv4()) {
        debugs(14, 3, "ACLARP::match: IPv4 Required for ARP Lookups. Skipping " << checklist->src_addr );
        return 0;
    }

    return aclMatchArp(&data, checklist->src_addr);
}