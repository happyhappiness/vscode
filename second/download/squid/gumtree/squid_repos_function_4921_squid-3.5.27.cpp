int
asnMatchIp(CbDataList<int> *data, Ip::Address &addr)
{
    struct squid_radix_node *rn;
    as_info *e;
    m_ADDR m_addr;
    CbDataList<int> *a = NULL;
    CbDataList<int> *b = NULL;

    debugs(53, 3, "asnMatchIp: Called for " << addr );

    if (AS_tree_head == NULL)
        return 0;

    if (addr.isNoAddr())
        return 0;

    if (addr.isAnyAddr())
        return 0;

    m_addr.addr = addr;

    rn = squid_rn_match(&m_addr, AS_tree_head);

    if (rn == NULL) {
        debugs(53, 3, "asnMatchIp: Address not in as db.");
        return 0;
    }

    debugs(53, 3, "asnMatchIp: Found in db!");
    e = ((rtentry_t *) rn)->e_info;
    assert(e);

    for (a = data; a; a = a->next)
        for (b = e->as_number; b; b = b->next)
            if (a->element == b->element) {
                debugs(53, 5, "asnMatchIp: Found a match!");
                return 1;
            }

    debugs(53, 5, "asnMatchIp: AS not in as db.");
    return 0;
}