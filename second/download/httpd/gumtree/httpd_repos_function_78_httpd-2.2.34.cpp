static void ssl_print_cert_info(BIO *bio, X509 *cert)
{
    X509_NAME *dn;
    char buf[1024];

    BIO_printf(bio, "Certificate version: %ld\n", X509_get_version(cert)+1);
    BIO_printf(bio,"Valid from: ");
    ASN1_UTCTIME_print(bio, X509_get_notBefore(cert));
    BIO_printf(bio,"\n");

    BIO_printf(bio,"Valid to  : ");
    ASN1_UTCTIME_print(bio, X509_get_notAfter(cert));
    BIO_printf(bio,"\n");

    BIO_printf(bio,"Public key is %d bits\n",
               EVP_PKEY_bits(X509_get_pubkey(cert)));

    dn = X509_get_issuer_name(cert);
    X509_NAME_oneline(dn, buf, sizeof(buf));
    BIO_printf(bio,"The issuer name is %s\n", buf);

    dn=X509_get_subject_name(cert);
    X509_NAME_oneline(dn, buf, sizeof(buf));
    BIO_printf(bio,"The subject name is %s\n", buf);

    /* dump the extension list too */
    BIO_printf(bio, "Extension Count: %d\n", X509_get_ext_count(cert));
}