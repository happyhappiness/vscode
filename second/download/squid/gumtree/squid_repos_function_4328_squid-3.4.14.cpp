void
Ssl::CertValidationMsg::composeRequest(CertValidationRequest const &vcert)
{
    body.clear();
    body += Ssl::CertValidationMsg::param_host + "=" + vcert.domainName;
    STACK_OF(X509) *peerCerts = static_cast<STACK_OF(X509) *>(SSL_get_ex_data(vcert.ssl, ssl_ex_index_ssl_cert_chain));

    if (!peerCerts)
        peerCerts = SSL_get_peer_cert_chain(vcert.ssl);

    if (peerCerts) {
        Ssl::BIO_Pointer bio(BIO_new(BIO_s_mem()));
        for (int i = 0; i < sk_X509_num(peerCerts); ++i) {
            X509 *cert = sk_X509_value(peerCerts, i);
            PEM_write_bio_X509(bio.get(), cert);
            body = body + "\n" + param_cert + xitoa(i) + "=";
            char *ptr;
            long len = BIO_get_mem_data(bio.get(), &ptr);
            body.append(ptr, (ptr[len-1] == '\n' ? len - 1 : len));
            if (!BIO_reset(bio.get())) {
                // print an error?
            }
        }
    }

    if (vcert.errors) {
        int i = 0;
        for (const Ssl::CertErrors *err = vcert.errors; err; err = err->next, ++i) {
            body +="\n";
            body = body + param_error_name + xitoa(i) + "=" + GetErrorName(err->element.code) + "\n";
            int errorCertPos = -1;
            if (err->element.cert.get())
                errorCertPos = sk_X509_find(peerCerts, err->element.cert.get());
            if (errorCertPos < 0) {
                // assert this error ?
                debugs(83, 4, "WARNING: wrong cert in cert validator request");
            }
            body += param_error_cert + xitoa(i) + "=";
            body += param_cert + xitoa((errorCertPos >= 0 ? errorCertPos : 0));
        }
    }
}