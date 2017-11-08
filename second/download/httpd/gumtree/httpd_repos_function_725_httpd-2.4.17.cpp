void *modssl_get_app_data2(SSL *ssl)
{
    return (void *)SSL_get_ex_data(ssl, app_data2_idx);
}