struct squid_radix_node *
squid_rn_lookup(void *v_arg, void *m_arg, struct squid_radix_node_head *head) {
    register struct squid_radix_node *x;
    caddr_t netmask = 0;

    if (m_arg) {
        if ((x = squid_rn_addmask(m_arg, 1, head->rnh_treetop->rn_off)) == 0)
            return (0);
        netmask = x->rn_key;
    }
    x = squid_rn_match(v_arg, head);
    if (x && netmask) {
        while (x && x->rn_mask != netmask)
            x = x->rn_dupedkey;
    }
    return x;
}