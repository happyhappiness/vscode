          || sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
        char *prompt;
        int i;

        if (sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
            if (!readtty) {
                ap_log_error(APLOG_MARK, APLOG_INFO, 0, ppcb_arg->s,
                             APLOGNO(01965)
                             "Init: Creating pass phrase dialog pipe child "
                             "'%s'", sc->server->pphrase_dialog_path);
                if (ssl_pipe_child_create(ppcb_arg->p,
                                          sc->server->pphrase_dialog_path)
                        != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, ppcb_arg->s,
                                 APLOGNO(01966)
                                 "Init: Failed to create pass phrase pipe '%s'",
                                 sc->server->pphrase_dialog_path);
                    PEMerr(PEM_F_PEM_DEF_CALLBACK,
                           PEM_R_PROBLEMS_GETTING_PASSWORD);
                    memset(buf, 0, (unsigned int)bufsize);
                    return (-1);
                }
            }
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, ppcb_arg->s, APLOGNO(01967)
                         "Init: Requesting pass phrase via piped dialog");
        }
        else { /* sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN */
#ifdef WIN32
            PEMerr(PEM_F_PEM_DEF_CALLBACK, PEM_R_PROBLEMS_GETTING_PASSWORD);
            memset(buf, 0, (unsigned int)bufsize);
            return (-1);
#else
            /*
             * stderr has already been redirected to the error_log.
             * rather than attempting to temporarily rehook it to the terminal,
             * we print the prompt to stdout before EVP_read_pw_string turns
             * off tty echo
             */
            apr_file_open_stdout(&writetty, ppcb_arg->p);

            ap_log_error(APLOG_MARK, APLOG_INFO, 0, ppcb_arg->s, APLOGNO(01968)
                         "Init: Requesting pass phrase via builtin terminal "
                         "dialog");
#endif
        }

        /*
         * The first time display a header to inform the user about what
         * program he actually speaks to, which module is responsible for
         * this terminal dialog and why to the hell he has to enter
         * something...
         */
        if (ppcb_arg->nPassPhraseDialog == 1) {
            apr_file_printf(writetty, "%s mod_ssl (Pass Phrase Dialog)\n",
                            AP_SERVER_BASEVERSION);
            apr_file_printf(writetty, "Some of your private key files are encrypted for security reasons.\n");
            apr_file_printf(writetty, "In order to read them you have to provide the pass phrases.\n");
        }
        if (ppcb_arg->bPassPhraseDialogOnce) {
            ppcb_arg->bPassPhraseDialogOnce = FALSE;
            apr_file_printf(writetty, "\n");
            apr_file_printf(writetty, "Private key %s (%s)\n",
                            ppcb_arg->key_id, ppcb_arg->pkey_file);
        }

        /*
         * Emulate the OpenSSL internal pass phrase dialog
         * (see crypto/pem/pem_lib.c:def_callback() for details)
         */
