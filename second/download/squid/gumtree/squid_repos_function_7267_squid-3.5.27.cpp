static struct squid_radix_mask *
rn_new_radix_mask(struct squid_radix_node *tt, struct squid_radix_mask *next) {
    register struct squid_radix_mask *m;

    squid_MKGet(m);
    if (m == 0) {
        fprintf(stderr, "Mask for route not entered\n");
        return (0);
    }
    memset(m, '\0', sizeof *m);
    m->rm_b = tt->rn_b;
    m->rm_flags = tt->rn_flags;
    if (tt->rn_flags & RNF_NORMAL)
        m->rm_leaf = tt;
    else
        m->rm_mask = tt->rn_mask;
    m->rm_mklist = next;
    tt->rn_mklist = m;
    return m;
}