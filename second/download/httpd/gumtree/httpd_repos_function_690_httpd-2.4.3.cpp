void ssl_stapling_ex_init(void)
{
    if (stapling_ex_idx != -1)
        return;
    stapling_ex_idx = X509_get_ex_new_index(0, "X509 cached OCSP info", 0, 0,
                                            certinfo_free);
}