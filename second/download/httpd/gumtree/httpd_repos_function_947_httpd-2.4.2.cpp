static DH *get_dh512(void)
{
    DH *dh;

    if (!(dh = DH_new())) {
        return NULL;
    }

    dh->p = BN_bin2bn(dh512_p, sizeof(dh512_p), NULL);
    dh->g = BN_bin2bn(dh512_g, sizeof(dh512_g), NULL);
    if (!(dh->p && dh->g)) {
        DH_free(dh);
        return NULL;
    }

    return dh;
}