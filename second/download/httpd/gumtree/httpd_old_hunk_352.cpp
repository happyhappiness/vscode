
    /*
     * Let the user know when we're successful.
     */
    if (nPassPhraseDialog > 0) {
        sc = mySrvConfig(s);
        if (sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN
              || sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
            apr_file_printf(writetty, "\n");
            apr_file_printf(writetty, "Ok: Pass Phrase Dialog successful.\n");
        }
    }

    /*
     * Wipe out the used memory from the
     * pass phrase array and then deallocate it
     */
    if (aPassPhrase->nelts) {
        pphrase_array_clear(aPassPhrase);
        ssl_log(s, SSL_LOG_INFO,
                "Init: Wiped out the queried pass phrases from memory");
    }

    /* Close the pipes if they were opened
     */
    if (readtty) {
        apr_file_close(readtty);
