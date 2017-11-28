static int
rn_satsifies_leaf(char *trial, register struct squid_radix_node *leaf, int skip)
{
    register char *cp = trial, *cp2 = leaf->rn_key, *cp3 = leaf->rn_mask;
    char *cplim;
    int length = min(*(u_char *) cp, *(u_char *) cp2);

    if (cp3 == 0)
        cp3 = rn_ones;
    else
        length = min(length, *(u_char *) cp3);
    cplim = cp + length;
    cp3 += skip;
    cp2 += skip;
    for (cp += skip; cp < cplim; cp++, cp2++, cp3++)
        if ((*cp ^ *cp2) & *cp3)
            return 0;
    return 1;
}