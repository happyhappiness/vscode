static DH *get_dh1024(void)
{
    DH *dh;

    if (!(dh = DH_new())) {
        return NULL;
    }

    dh->p = BN_bin2bn(dh1024_p, sizeof(dh1024_p), NULL);
    dh->g = BN_bin2bn(dh1024_g, sizeof(dh1024_g), NULL);
    if (!(dh->p && dh->g)) {
        DH_free(dh);
        return NULL;
    }

    return dh;
}