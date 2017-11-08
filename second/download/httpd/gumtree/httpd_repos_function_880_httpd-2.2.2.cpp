static DH *get_dh512(void)
{
    return modssl_dh_configure(dh512_p, sizeof(dh512_p),
                               dh512_g, sizeof(dh512_g));
}