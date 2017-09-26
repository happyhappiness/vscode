         * something...
         */
        if (*pnPassPhraseDialog == 1) {
            apr_file_printf(writetty, "%s mod_ssl/%s (Pass Phrase Dialog)\n",
                            AP_SERVER_BASEVERSION, MOD_SSL_VERSION);
            apr_file_printf(writetty, "Some of your private key files are encrypted for security reasons.\n");
            apr_file_printf(writetty, "In order to read them you have to provide the pass phrases.\n");
        }
        if (*pbPassPhraseDialogOnce) {
            *pbPassPhraseDialogOnce = FALSE;
            apr_file_printf(writetty, "\n");
            apr_file_printf(writetty, "Server %s (%s)\n", cpVHostID, cpAlgoType);
        }
