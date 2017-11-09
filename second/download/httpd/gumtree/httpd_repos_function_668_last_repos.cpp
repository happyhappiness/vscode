static DH *make_dh_params(BIGNUM *(*prime)(BIGNUM *))
{
    DH *dh = DH_new();
    BIGNUM *p, *g;

    if (!dh) {
        return NULL;
    }
    p = prime(NULL);
    g = BN_new();
    if (g != NULL) {
        BN_set_word(g, 2);
    }
    if (!p || !g || !DH_set0_pqg(dh, p, NULL, g)) {
        DH_free(dh);
        BN_free(p);
        BN_free(g);
        return NULL;
    }
    return dh;
}