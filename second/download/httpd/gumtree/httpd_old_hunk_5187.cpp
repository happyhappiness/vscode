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

