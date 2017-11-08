static DH *get_dh8192(void)
{
    return modssl_dh_configure(dh8192_p, sizeof(dh8192_p),
                               dh8192_g, sizeof(dh8192_g));
}