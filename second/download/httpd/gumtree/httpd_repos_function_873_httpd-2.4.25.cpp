void ssl_hook_ConfigTest(apr_pool_t *pconf, server_rec *s)
{
    apr_file_t *out = NULL;
    if (!ap_exists_config_define("DUMP_CERTS")) {
        return;
    }
    apr_file_open_stdout(&out, pconf);
    apr_file_printf(out, "Server certificates:\n");

    /* Dump the filenames of all configured server certificates to
     * stdout. */
    while (s) {
        SSLSrvConfigRec *sc = mySrvConfig(s);

        if (sc && sc->server && sc->server->pks) {
            modssl_pk_server_t *const pks = sc->server->pks;
            int i;

            for (i = 0; (i < pks->cert_files->nelts) &&
                        APR_ARRAY_IDX(pks->cert_files, i, const char *);
                 i++) {
                apr_file_printf(out, "  %s\n",
                                APR_ARRAY_IDX(pks->cert_files,
                                              i, const char *));
            }
        }

        s = s->next;
    }

}