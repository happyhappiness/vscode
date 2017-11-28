static int
asnAddNet(char *as_string, int as_number)
{
    struct squid_radix_node *rn;
    CbDataList<int> **Tail = NULL;
    CbDataList<int> *q = NULL;
    as_info *asinfo = NULL;

    Ip::Address mask;
    Ip::Address addr;
    char *t;
    int bitl;

    t = strchr(as_string, '/');

    if (t == NULL) {
        debugs(53, 3, "asnAddNet: failed, invalid response from whois server.");
        return 0;
    }

    *t = '\0';
    addr = as_string;
    bitl = atoi(t + 1);

    if (bitl < 0)
        bitl = 0;

    // INET6 TODO : find a better way of identifying the base IPA family for mask than this.
    t = strchr(as_string, '.');

    // generate Netbits Format Mask
    mask.SetNoAddr();
    mask.ApplyMask(bitl, (t!=NULL?AF_INET:AF_INET6) );

    debugs(53, 3, "asnAddNet: called for " << addr << "/" << mask );

    rtentry_t *e = (rtentry_t *)xcalloc(1, sizeof(rtentry_t));

    e->e_addr.addr = addr;

    e->e_mask.addr = mask;

    rn = squid_rn_lookup(&e->e_addr, &e->e_mask, AS_tree_head);

    if (rn != NULL) {
        asinfo = ((rtentry_t *) rn)->e_info;

        if (asinfo->as_number->find(as_number)) {
            debugs(53, 3, "asnAddNet: Ignoring repeated network '" << addr << "/" << bitl << "' for AS " << as_number);
        } else {
            debugs(53, 3, "asnAddNet: Warning: Found a network with multiple AS numbers!");

            for (Tail = &asinfo->as_number; *Tail; Tail = &(*Tail)->next);
            q = new CbDataList<int> (as_number);

            *(Tail) = q;

            e->e_info = asinfo;
        }
    } else {
        q = new CbDataList<int> (as_number);
        asinfo = (as_info *)xmalloc(sizeof(as_info));
        asinfo->as_number = q;
        rn = squid_rn_addroute(&e->e_addr, &e->e_mask, AS_tree_head, e->e_nodes);
        rn = squid_rn_match(&e->e_addr, AS_tree_head);
        assert(rn != NULL);
        e->e_info = asinfo;
    }

    if (rn == 0) { 		/* assert might expand to nothing */
        xfree(asinfo);
        delete q;
        xfree(e);
        debugs(53, 3, "asnAddNet: Could not add entry.");
        return 0;
    }

    e->e_info = asinfo;
    return 1;
}