int ssl_hook_UserCheck(request_rec *r)
{
    SSLConnRec *sslconn = myConnConfig(r->connection);
    SSLSrvConfigRec *sc = mySrvConfig(r->server);
    SSLDirConfigRec *dc = myDirConfig(r);
    char *clientdn;
    const char *auth_line, *username, *password;

    /*
     * Additionally forbid access (again)
     * when strict require option is used.
     */
    if ((dc->nOptions & SSL_OPT_STRICTREQUIRE) &&
        (apr_table_get(r->notes, "ssl-access-forbidden")))
    {
        return HTTP_FORBIDDEN;
    }

    /*
     * We decline when we are in a subrequest.  The Authorization header
     * would already be present if it was added in the main request.
     */
    if (!ap_is_initial_req(r)) {
        return DECLINED;
    }

    /*
     * Make sure the user is not able to fake the client certificate
     * based authentication by just entering an X.509 Subject DN
     * ("/XX=YYY/XX=YYY/..") as the username and "password" as the
     * password.
     */
    if ((auth_line = apr_table_get(r->headers_in, "Authorization"))) {
        if (strcEQ(ap_getword(r->pool, &auth_line, ' '), "Basic")) {
            while ((*auth_line == ' ') || (*auth_line == '\t')) {
                auth_line++;
            }

            auth_line = ap_pbase64decode(r->pool, auth_line);
            username = ap_getword_nulls(r->pool, &auth_line, ':');
            password = auth_line;

            if ((username[0] == '/') && strEQ(password, "password")) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "Encountered FakeBasicAuth spoof: %s", username);
                return HTTP_FORBIDDEN;
            }
        }
    }

    /*
     * We decline operation in various situations...
     * - SSLOptions +FakeBasicAuth not configured
     * - r->user already authenticated
     * - ssl not enabled
     * - client did not present a certificate
     */
    if (!(sc->enabled && sslconn && sslconn->ssl && sslconn->client_cert) ||
        !(dc->nOptions & SSL_OPT_FAKEBASICAUTH) || r->user)
    {
        return DECLINED;
    }
    
    if (!sslconn->client_dn) {
        X509_NAME *name = X509_get_subject_name(sslconn->client_cert);
        char *cp = X509_NAME_oneline(name, NULL, 0);
        sslconn->client_dn = apr_pstrdup(r->connection->pool, cp);
        modssl_free(cp);
    }

    clientdn = (char *)sslconn->client_dn;

    /*
     * Fake a password - which one would be immaterial, as, it seems, an empty
     * password in the users file would match ALL incoming passwords, if only
     * we were using the standard crypt library routine. Unfortunately, OpenSSL
     * "fixes" a "bug" in crypt and thus prevents blank passwords from
     * working.  (IMHO what they really fix is a bug in the users of the code
     * - failing to program correctly for shadow passwords).  We need,
     * therefore, to provide a password. This password can be matched by
     * adding the string "xxj31ZMTZzkVA" as the password in the user file.
     * This is just the crypted variant of the word "password" ;-)
     */
    auth_line = apr_pstrcat(r->pool, "Basic ", 
                            ap_pbase64encode(r->pool, 
                                             apr_pstrcat(r->pool, clientdn, 
                                                         ":password", NULL)),
                            NULL);
    apr_table_set(r->headers_in, "Authorization", auth_line);

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "Faking HTTP Basic Auth header: \"Authorization: %s\"",
                 auth_line);

    return DECLINED;
}