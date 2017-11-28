static int
ssl_load_crl(SSL_CTX *sslContext, const char *CRLfile)
{
    X509_STORE *st = SSL_CTX_get_cert_store(sslContext);
    X509_CRL *crl;
    BIO *in = BIO_new_file(CRLfile, "r");
    int count = 0;

    if (!in) {
        debugs(83, 2, "WARNING: Failed to open CRL file '" << CRLfile << "'");
        return 0;
    }

    while ((crl = PEM_read_bio_X509_CRL(in,NULL,NULL,NULL))) {
        if (!X509_STORE_add_crl(st, crl))
            debugs(83, 2, "WARNING: Failed to add CRL from file '" << CRLfile << "'");
        else
            ++count;

        X509_CRL_free(crl);
    }

    BIO_free(in);
    return count;
}