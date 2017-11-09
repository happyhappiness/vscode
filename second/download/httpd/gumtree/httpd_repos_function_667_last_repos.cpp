static int DH_set0_pqg(DH *dh, BIGNUM *p, BIGNUM *q, BIGNUM *g)
{
    /* q is optional */
    if (p == NULL || g == NULL)
        return 0;
    BN_free(dh->p);
    BN_free(dh->q);
    BN_free(dh->g);
    dh->p = p;
    dh->q = q;
    dh->g = g;

    if (q != NULL) {
        dh->length = BN_num_bits(q);
    }

    return 1;
}