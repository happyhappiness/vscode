void
squid_rn_init(void)
{
    char *cp, *cplim;
#ifdef KERNEL
    struct domain *dom;

    for (dom = domains; dom; dom = dom->dom_next)
        if (dom->dom_maxrtkey > squid_max_keylen)
            squid_max_keylen = dom->dom_maxrtkey;
#endif
    if (squid_max_keylen == 0) {
        fprintf(stderr,
                "squid_rn_init: radix functions require squid_max_keylen be set\n");
        return;
    }
    squid_R_Malloc(rn_zeros, char *, 3 * squid_max_keylen);
    if (rn_zeros == NULL) {
        fprintf(stderr, "squid_rn_init failed.\n");
        exit(-1);
    }
    memset(rn_zeros, '\0', 3 * squid_max_keylen);
    rn_ones = cp = rn_zeros + squid_max_keylen;
    addmask_key = cplim = rn_ones + squid_max_keylen;
    while (cp < cplim)
        *cp++ = -1;
    if (squid_rn_inithead(&squid_mask_rnhead, 0) == 0) {
        fprintf(stderr, "rn_init2 failed.\n");
        exit(-1);
    }
}