void
Ssl::SSL_add_untrusted_cert(SSL *ssl, X509 *cert)
{
    STACK_OF(X509) *untrustedStack = static_cast <STACK_OF(X509) *>(SSL_get_ex_data(ssl, ssl_ex_index_ssl_untrusted_chain));
    if (!untrustedStack) {
        untrustedStack = sk_X509_new_null();
        if (!SSL_set_ex_data(ssl, ssl_ex_index_ssl_untrusted_chain, untrustedStack)) {
            sk_X509_pop_free(untrustedStack, X509_free);
            throw TextException("Failed to attach untrusted certificates chain");
        }
    }
    sk_X509_push(untrustedStack, cert);
}