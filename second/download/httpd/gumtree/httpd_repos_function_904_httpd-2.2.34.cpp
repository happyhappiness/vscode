static DH *get_dh2048(void)
{
    return modssl_dh_configure(dh2048_p, sizeof(dh2048_p),
                               dh2048_g, sizeof(dh2048_g));
}