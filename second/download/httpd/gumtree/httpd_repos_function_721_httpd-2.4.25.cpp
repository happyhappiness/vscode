void modssl_set_app_data2(SSL *ssl, void *arg)
{
    SSL_set_ex_data(ssl, app_data2_idx, (char *)arg);
    return;
}