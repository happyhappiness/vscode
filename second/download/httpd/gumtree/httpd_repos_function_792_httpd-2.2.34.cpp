static const char *ssl_cmd_protocol_parse(cmd_parms *parms,
                                          const char *arg,
                                          ssl_proto_t *options)
{
    ssl_proto_t thisopt;

    *options = SSL_PROTOCOL_NONE;

    while (*arg) {
        char *w = ap_getword_conf(parms->temp_pool, &arg);
        char action = '\0';

        if ((*w == '+') || (*w == '-')) {
            action = *(w++);
        }

        if (strcEQ(w, "SSLv2")) {
#ifdef OPENSSL_NO_SSL2
            if (action != '-') {
                return "SSLv2 not supported by this version of OpenSSL";
            }
            /* Nothing to do, the flag is not present to be toggled */
            continue;
#else
            thisopt = SSL_PROTOCOL_SSLV2;
#endif
        }
        else if (strcEQ(w, "SSLv3")) {
#ifdef OPENSSL_NO_SSL3
            if (action != '-') {
                return "SSLv3 not supported by this version of OpenSSL";
            }
            /* Nothing to do, the flag is not present to be toggled */
            continue;
#else
            thisopt = SSL_PROTOCOL_SSLV3;
#endif
        }
        else if (strcEQ(w, "TLSv1")) {
            thisopt = SSL_PROTOCOL_TLSV1;
        }
#ifdef HAVE_TLSV1_X
        else if (strcEQ(w, "TLSv1.1")) {
            thisopt = SSL_PROTOCOL_TLSV1_1;
        }
        else if (strcEQ(w, "TLSv1.2")) {
            thisopt = SSL_PROTOCOL_TLSV1_2;
        }
#endif
        else if (strcEQ(w, "all")) {
            thisopt = SSL_PROTOCOL_ALL;
        }
        else {
            return apr_pstrcat(parms->temp_pool,
                               parms->cmd->name,
                               ": Illegal protocol '",
                               w, "'", NULL);
        }

        if (action == '-') {
            *options &= ~thisopt;
        }
        else if (action == '+') {
            *options |= thisopt;
        }
        else {
            *options = thisopt;
        }
    }

    return NULL;
}