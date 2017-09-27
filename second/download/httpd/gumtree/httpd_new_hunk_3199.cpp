    }

    /*
     * Let the user know when we're successful.
     */
    if (nPassPhraseDialog > 0) {
        if (writetty) {
            apr_file_printf(writetty, "\n"
                            "OK: Pass Phrase Dialog successful.\n");
        }
    }

    /*
     * Wipe out the used memory from the
     * pass phrase array and then deallocate it
     */
    if (aPassPhrase->nelts) {
        pphrase_array_clear(aPassPhrase);
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02205)
                     "Init: Wiped out the queried pass phrases from memory");
    }

    /* Close the pipes if they were opened
     */
    if (readtty) {
