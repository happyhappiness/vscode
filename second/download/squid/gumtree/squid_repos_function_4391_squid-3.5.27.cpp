void
Ssl::Bio::Link(SSL *ssl, BIO *bio)
{
    SSL_set_bio(ssl, bio, bio); // cannot fail
    SSL_set_info_callback(ssl, &squid_ssl_info); // does not provide diagnostic
}