static DH *get_dh4096(void)
{
    return modssl_dh_configure(dh4096_p, sizeof(dh4096_p),
                               dh4096_g, sizeof(dh4096_g));
}