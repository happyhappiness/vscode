int
squid_rn_inithead(struct squid_radix_node_head **head, int off)
{
    register struct squid_radix_node_head *rnh;
    register struct squid_radix_node *t, *tt, *ttt;
    if (*head)
        return (1);
    squid_R_Malloc(rnh, struct squid_radix_node_head *, sizeof(*rnh));
    if (rnh == 0)
        return (0);
    memset(rnh, '\0', sizeof(*rnh));
    *head = rnh;
    t = squid_rn_newpair(rn_zeros, off, rnh->rnh_nodes);
    ttt = rnh->rnh_nodes + 2;
    t->rn_r = ttt;
    t->rn_p = t;
    tt = t->rn_l;
    tt->rn_flags = t->rn_flags = RNF_ROOT | RNF_ACTIVE;
    tt->rn_b = -1 - off;
    *ttt = *tt;
    ttt->rn_key = rn_ones;
    rnh->rnh_addaddr = squid_rn_addroute;
    rnh->rnh_deladdr = squid_rn_delete;
    rnh->rnh_matchaddr = squid_rn_match;
    rnh->rnh_lookup = squid_rn_lookup;
    rnh->rnh_walktree = squid_rn_walktree;
    rnh->rnh_treetop = t;
    return (1);
}