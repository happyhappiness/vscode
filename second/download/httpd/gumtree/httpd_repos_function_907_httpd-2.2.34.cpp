static DH *get_dh6144(void)
{
    return modssl_dh_configure(dh6144_p, sizeof(dh6144_p),
                               dh6144_g, sizeof(dh6144_g));
}