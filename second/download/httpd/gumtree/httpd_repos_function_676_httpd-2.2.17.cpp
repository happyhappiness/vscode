DH *modssl_dh_configure(unsigned char *p, int plen,
                        unsigned char *g, int glen)
{
    DH *dh;

    if (!(dh = DH_new())) {
        return NULL;
    }

#if defined(OPENSSL_VERSION_NUMBER) || (SSLC_VERSION_NUMBER < 0x2000)
    dh->p = BN_bin2bn(p, plen, NULL);
    dh->g = BN_bin2bn(g, glen, NULL);
    if (!(dh->p && dh->g)) {
        DH_free(dh);
        return NULL;
    }
#else
    R_EITEMS_add(dh->data, PK_TYPE_DH, PK_DH_P, 0, p, plen, R_EITEMS_PF_COPY);
    R_EITEMS_add(dh->data, PK_TYPE_DH, PK_DH_G, 0, g, glen, R_EITEMS_PF_COPY);
#endif

    return dh;
}