static DH *make_dh_params(BIGNUM *(*prime)(BIGNUM *), const char *gen)
{
    DH *dh = DH_new();

    if (!dh) {
        return NULL;
    }
    dh->p = prime(NULL);
    BN_dec2bn(&dh->g, gen);
    if (!dh->p || !dh->g) {
        DH_free(dh);
        return NULL;
    }
    return dh;
}