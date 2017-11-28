struct squid_radix_node *
squid_rn_newpair(void *v, int b, struct squid_radix_node nodes[2]) {
    register struct squid_radix_node *tt = nodes, *t = tt + 1;
    t->rn_b = b;
    t->rn_bmask = 0x80 >> (b & 7);
    t->rn_l = tt;
    t->rn_off = b >> 3;
    tt->rn_b = -1;
    tt->rn_key = (caddr_t) v;
    tt->rn_p = t;
    tt->rn_flags = t->rn_flags = RNF_ACTIVE;
#ifdef RN_DEBUG
    tt->rn_info = rn_nodenum++;
    t->rn_info = rn_nodenum++;
    tt->rn_twin = t;
    tt->rn_ybro = rn_clist;
    rn_clist = tt;
#endif
    return t;
}