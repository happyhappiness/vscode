struct squid_radix_node *
squid_rn_search_m(void *v_arg, struct squid_radix_node *head, void *m_arg) {
    register struct squid_radix_node *x;
    register caddr_t v = v_arg, m = m_arg;

    for (x = head; x->rn_b >= 0;) {
        if ((x->rn_bmask & m[x->rn_off]) &&
                (x->rn_bmask & v[x->rn_off]))
            x = x->rn_r;
        else
            x = x->rn_l;
    }
    return x;
}