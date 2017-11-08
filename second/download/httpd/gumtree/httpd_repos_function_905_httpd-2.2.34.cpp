static DH *get_dh3072(void)
{
    return modssl_dh_configure(dh3072_p, sizeof(dh3072_p),
                               dh3072_g, sizeof(dh3072_g));
}