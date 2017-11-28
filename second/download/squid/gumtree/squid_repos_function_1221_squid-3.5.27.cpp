static void parse_sslproxy_cert_adapt(sslproxy_cert_adapt **cert_adapt)
{
    char *al;
    sslproxy_cert_adapt *ca = (sslproxy_cert_adapt *) xcalloc(1, sizeof(sslproxy_cert_adapt));
    if ((al = ConfigParser::NextToken()) == NULL) {
        self_destruct();
        return;
    }

    const char *param;
    if ( char *s = strchr(al, '{')) {
        *s = '\0'; // terminate the al string
        ++s;
        param = s;
        s = strchr(s, '}');
        if (!s) {
            self_destruct();
            return;
        }
        *s = '\0';
    } else
        param = NULL;

    if (strcmp(al, Ssl::CertAdaptAlgorithmStr[Ssl::algSetValidAfter]) == 0) {
        ca->alg = Ssl::algSetValidAfter;
        ca->param = xstrdup("on");
    } else if (strcmp(al, Ssl::CertAdaptAlgorithmStr[Ssl::algSetValidBefore]) == 0) {
        ca->alg = Ssl::algSetValidBefore;
        ca->param = xstrdup("on");
    } else if (strcmp(al, Ssl::CertAdaptAlgorithmStr[Ssl::algSetCommonName]) == 0) {
        ca->alg = Ssl::algSetCommonName;
        if (param) {
            if (strlen(param) > 64) {
                debugs(3, DBG_CRITICAL, "FATAL: sslproxy_cert_adapt: setCommonName{" <<param << "} : using common name longer than 64 bytes is not supported");
                self_destruct();
                return;
            }
            ca->param = xstrdup(param);
        }
    } else {
        debugs(3, DBG_CRITICAL, "FATAL: sslproxy_cert_adapt: unknown cert adaptation algorithm: " << al);
        self_destruct();
        return;
    }

    aclParseAclList(LegacyParser, &ca->aclList, al);

    while (*cert_adapt)
        cert_adapt = &(*cert_adapt)->next;

    *cert_adapt = ca;
}