bool
Ssl::Bio::sslFeatures::get(const SSL *ssl)
{
    sslVersion = SSL_version(ssl);
    debugs(83, 7, "SSL version: " << SSL_get_version(ssl) << " (" << sslVersion << ")");

#if defined(TLSEXT_NAMETYPE_host_name)
    if (const char *server = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name))
        serverName = server;
    debugs(83, 7, "SNI server name: " << serverName);
#endif

#if !defined(OPENSSL_NO_COMP)
    if (ssl->session->compress_meth)
        compressMethod = ssl->session->compress_meth;
    else if (sslVersion >= 3) //if it is 3 or newer version then compression is disabled
#endif
        compressMethod = 0;
    debugs(83, 7, "SSL compression: " << compressMethod);

    STACK_OF(SSL_CIPHER) * ciphers = NULL;
    if (ssl->server)
        ciphers = ssl->session->ciphers;
    else
        ciphers = ssl->cipher_list;
    if (ciphers) {
        for (int i = 0; i < sk_SSL_CIPHER_num(ciphers); ++i) {
            SSL_CIPHER *c = sk_SSL_CIPHER_value(ciphers, i);
            if (c != NULL) {
                if (!clientRequestedCiphers.empty())
                    clientRequestedCiphers.append(":");
                clientRequestedCiphers.append(c->name);
            }
        }
    }
    debugs(83, 7, "Ciphers requested by client: " << clientRequestedCiphers);

    if (sslVersion >=3 && ssl->s3 && ssl->s3->client_random[0]) {
        memcpy(client_random, ssl->s3->client_random, SSL3_RANDOM_SIZE);
    }

#if 0 /* XXX: OpenSSL 0.9.8k lacks at least some of these tlsext_* fields */
    //The following extracted for logging purpuses:
    // TLSEXT_TYPE_ec_point_formats
    unsigned char *p;
    int len;
    if (ssl->server) {
        p = ssl->session->tlsext_ecpointformatlist;
        len = ssl->session->tlsext_ecpointformatlist_length;
    } else {
        p = ssl->tlsext_ecpointformatlist;
        len = ssl->tlsext_ecpointformatlist_length;
    }
    if (p) {
        ecPointFormatList = objToString(p, len);
        debugs(83, 7, "tlsExtension ecPointFormatList of length " << len << " :" << ecPointFormatList);
    }

    // TLSEXT_TYPE_elliptic_curves
    if (ssl->server) {
        p = ssl->session->tlsext_ellipticcurvelist;
        len = ssl->session->tlsext_ellipticcurvelist_length;
    } else {
        p = ssl->tlsext_ellipticcurvelist;
        len = ssl->tlsext_ellipticcurvelist_length;
    }
    if (p) {
        ellipticCurves = objToString(p, len);
        debugs(83, 7, "tlsExtension ellipticCurveList of length " <<  len <<" :" << ellipticCurves);
    }
    // TLSEXT_TYPE_opaque_prf_input
    p = NULL;
    if (ssl->server) {
        if (ssl->s3 &&  ssl->s3->client_opaque_prf_input) {
            p = (unsigned char *)ssl->s3->client_opaque_prf_input;
            len = ssl->s3->client_opaque_prf_input_len;
        }
    } else {
        p = (unsigned char *)ssl->tlsext_opaque_prf_input;
        len = ssl->tlsext_opaque_prf_input_len;
    }
    if (p) {
        debugs(83, 7, "tlsExtension client-opaque-prf-input of length " << len);
        opaquePrf = objToString(p, len);
    }
#endif
    initialized_ = true;
    return true;
}