struct squid_radix_node *
squid_rn_search(void *v_arg, struct squid_radix_node *head) {
    register struct squid_radix_node *x;
    register caddr_t v;

    for (x = head, v = v_arg; x->rn_b >= 0;) {
        if (x->rn_bmask & v[x->rn_off])
            x = x->rn_r;
        else
            x = x->rn_l;
    }
    return (x);
}