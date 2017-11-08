void ssl_hook_ConfigTest(apr_pool_t *pconf, server_rec *s)
{
    if (!ap_exists_config_define("DUMP_CERTS")) {
        return;
    }

    /* Dump the filenames of all configured server certificates to
     * stdout. */
    while (s) {
        SSLSrvConfigRec *sc = mySrvConfig(s);

        if (sc && sc->server && sc->server->pks) {
            modssl_pk_server_t *const pks = sc->server->pks;
            int i;

            for (i = 0; (i < SSL_AIDX_MAX) && pks->cert_files[i]; i++) {
                printf("%s\n", pks->cert_files[i]);
            }
        }

        s = s->next;
    }

}