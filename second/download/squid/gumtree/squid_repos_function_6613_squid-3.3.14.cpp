struct squid_radix_node *
squid_rn_addmask(void *n_arg, int search, int skip) {
    caddr_t netmask = (caddr_t) n_arg;
    register struct squid_radix_node *x;
    register caddr_t cp, cplim;
    register int b = 0, mlen, j;
    int maskduplicated, m0, isnormal;
    struct squid_radix_node *saved_x;
    static int last_zeroed = 0;

    if ((mlen = *(u_char *) netmask) > squid_max_keylen)
        mlen = squid_max_keylen;
    if (skip == 0)
        skip = 1;
    if (mlen <= skip)
        return (squid_mask_rnhead->rnh_nodes);
    if (skip > 1)
        memcpy(addmask_key + 1, rn_ones + 1, skip - 1);
    if ((m0 = mlen) > skip)
        memcpy(addmask_key + skip, netmask + skip, mlen - skip);
    /*
     * Trim trailing zeroes.
     */
    for (cp = addmask_key + mlen; (cp > addmask_key) && cp[-1] == 0;)
        cp--;
    mlen = cp - addmask_key;
    if (mlen <= skip) {
        if (m0 >= last_zeroed)
            last_zeroed = mlen;
        return (squid_mask_rnhead->rnh_nodes);
    }
    if (m0 < last_zeroed)
        memset(addmask_key + m0, '\0', last_zeroed - m0);
    *addmask_key = last_zeroed = mlen;
    x = squid_rn_search(addmask_key, rn_masktop);
    if (memcmp(addmask_key, x->rn_key, mlen) != 0)
        x = 0;
    if (x || search)
        return (x);
    squid_R_Malloc(x, struct squid_radix_node *, squid_max_keylen + 2 * sizeof(*x));
    if ((saved_x = x) == 0)
        return (0);
    memset(x, '\0', squid_max_keylen + 2 * sizeof(*x));
    netmask = cp = (caddr_t) (x + 2);
    memcpy(cp, addmask_key, mlen);
    x = squid_rn_insert(cp, squid_mask_rnhead, &maskduplicated, x);
    if (maskduplicated) {
        fprintf(stderr, "squid_rn_addmask: mask impossibly already in tree");
        squid_Free(saved_x);
        return (x);
    }
    /*
     * Calculate index of mask, and check for normalcy.
     */
    cplim = netmask + mlen;
    isnormal = 1;
    for (cp = netmask + skip; (cp < cplim) && *(u_char *) cp == 0xff;)
        cp++;
    if (cp != cplim) {
        for (j = 0x80; (j & *cp) != 0; j >>= 1)
            b++;
        if (*cp != normal_chars[b] || cp != (cplim - 1))
            isnormal = 0;
    }
    b += (cp - netmask) << 3;
    x->rn_b = -1 - b;
    if (isnormal)
        x->rn_flags |= RNF_NORMAL;
    return (x);
}