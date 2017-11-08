static DH *get_dh1024(void)
{
    return modssl_dh_configure(dh1024_p, sizeof(dh1024_p),
                               dh1024_g, sizeof(dh1024_g));
}