}

#endif /* HAVE_OCSP_STAPLING */

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

            for (i = 0; (i < SSL_AIDX_MAX) && pks->cert_files[i]; i++) {
                apr_file_printf(out, "  %s\n", pks->cert_files[i]);
            }
        }

        s = s->next;
    }

