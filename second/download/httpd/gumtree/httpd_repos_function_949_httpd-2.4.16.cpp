static char *ssl_var_lookup_ssl_cert_rfc4523_cea(apr_pool_t *p, SSL *ssl)
{
    char *result;
    X509 *xs;

    ASN1_INTEGER *serialNumber;

    if (!(xs = SSL_get_peer_certificate(ssl))) {
        return NULL;
    }

    result = NULL;

    serialNumber = X509_get_serialNumber(xs);
    if (serialNumber) {
        X509_NAME *issuer = X509_get_issuer_name(xs);
        if (issuer) {
            BIGNUM *bn = ASN1_INTEGER_to_BN(serialNumber, NULL);
            char *decimal = BN_bn2dec(bn);
            result = apr_pstrcat(p, "{ serialNumber ", decimal,
                    ", issuer rdnSequence:\"",
                    SSL_X509_NAME_to_string(p, issuer, 0), "\" }", NULL);
            OPENSSL_free(decimal);
            BN_free(bn);
        }
    }

    X509_free(xs);
    return result;
}