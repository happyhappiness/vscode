static int ssl_print_connection_info(BIO *bio, SSL *ssl)
{
    SSL_CIPHER *c;
    int alg_bits,bits;

    c = SSL_get_current_cipher(ssl);
    BIO_printf(bio,"Cipher Suite Protocol   :%s\n", SSL_CIPHER_get_version(c));
    BIO_printf(bio,"Cipher Suite Name       :%s\n",SSL_CIPHER_get_name(c));

    bits = SSL_CIPHER_get_bits(c,&alg_bits);
    BIO_printf(bio,"Cipher Suite Cipher Bits:%d (%d)\n",bits,alg_bits);

    return(1);
}