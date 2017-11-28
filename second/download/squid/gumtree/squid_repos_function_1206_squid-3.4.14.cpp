static void parse_sslproxy_cert_sign(sslproxy_cert_sign **cert_sign)
{
    char *al;
    sslproxy_cert_sign *cs = (sslproxy_cert_sign *) xcalloc(1, sizeof(sslproxy_cert_sign));
    if ((al = strtok(NULL, w_space)) == NULL) {
        self_destruct();
        return;
    }

    if (strcmp(al, Ssl::CertSignAlgorithmStr[Ssl::algSignTrusted]) == 0)
        cs->alg = Ssl::algSignTrusted;
    else if (strcmp(al, Ssl::CertSignAlgorithmStr[Ssl::algSignUntrusted]) == 0)
        cs->alg = Ssl::algSignUntrusted;
    else if (strcmp(al, Ssl::CertSignAlgorithmStr[Ssl::algSignSelf]) == 0)
        cs->alg = Ssl::algSignSelf;
    else {
        debugs(3, DBG_CRITICAL, "FATAL: sslproxy_cert_sign: unknown cert signing algorithm: " << al);
        self_destruct();
        return;
    }

    aclParseAclList(LegacyParser, &cs->aclList, al);

    while (*cert_sign)
        cert_sign = &(*cert_sign)->next;

    *cert_sign = cs;
}