int ssl_print_cert_info(bio,x509cert)
BIO *bio;
X509 *x509cert;
{
        X509_NAME *dn;
        char buf[64];

        BIO_printf(bio,"Certificate version: %d\n",X509_get_version(x509cert)+1);

        BIO_printf(bio,"Valid from: ");
        ASN1_UTCTIME_print(bio, X509_get_notBefore(x509cert));
        BIO_printf(bio,"\n");

        BIO_printf(bio,"Valid to  : ");
        ASN1_UTCTIME_print(bio, X509_get_notAfter(x509cert));
        BIO_printf(bio,"\n");

        BIO_printf(bio,"Public key is %d bits\n",
            EVP_PKEY_bits(X509_get_pubkey(x509cert)));

        dn=X509_get_issuer_name(x509cert);
        X509_NAME_oneline(dn, buf, BUFSIZ);
        BIO_printf(bio,"The issuer name is %s\n", buf);

        dn=X509_get_subject_name(x509cert);
        X509_NAME_oneline(dn, buf, BUFSIZ);
        BIO_printf(bio,"The subject name is %s\n", buf);

        /* dump the extension list too */
        BIO_printf(bio,"Extension Count: %d\n",X509_get_ext_count(x509cert));

        return(1);
}