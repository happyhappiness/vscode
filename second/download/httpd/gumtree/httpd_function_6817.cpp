int ssl_pphrase_Handle_CB(char *buf, int bufsize, int verify, void *srv)
{
    SSLModConfigRec *mc;
    server_rec *s;
    apr_pool_t *p;
    apr_array_header_t *aPassPhrase;
    SSLSrvConfigRec *sc;
    int *pnPassPhraseCur;
    char **cppPassPhraseCur;
    char *cpVHostID;
    char *cpAlgoType;
    int *pnPassPhraseDialog;
    int *pnPassPhraseDialogCur;
    BOOL *pbPassPhraseDialogOnce;
    char *cpp;
    int len = -1;

    mc = myModConfig((server_rec *)srv);

    /*
     * Reconnect to the context of ssl_phrase_Handle()
     */
    s                      = myCtxVarGet(mc,  1, server_rec *);
    p                      = myCtxVarGet(mc,  2, apr_pool_t *);
    aPassPhrase            = myCtxVarGet(mc,  3, apr_array_header_t *);
    pnPassPhraseCur        = myCtxVarGet(mc,  4, int *);
    cppPassPhraseCur       = myCtxVarGet(mc,  5, char **);
    cpVHostID              = myCtxVarGet(mc,  6, char *);
    cpAlgoType             = myCtxVarGet(mc,  7, char *);
    pnPassPhraseDialog     = myCtxVarGet(mc,  8, int *);
    pnPassPhraseDialogCur  = myCtxVarGet(mc,  9, int *);
    pbPassPhraseDialogOnce = myCtxVarGet(mc, 10, BOOL *);
    sc                     = mySrvConfig(s);

    (*pnPassPhraseDialog)++;
    (*pnPassPhraseDialogCur)++;

    /*
     * When remembered pass phrases are available use them...
     */
    if ((cpp = pphrase_array_get(aPassPhrase, *pnPassPhraseCur)) != NULL) {
        apr_cpystrn(buf, cpp, bufsize);
        len = strlen(buf);
        return len;
    }

    /*
     * Builtin or Pipe dialog
     */
    if (sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN
          || sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
        char *prompt;
        int i;

        if (sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
            if (!readtty) {
                ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01965)
                             "Init: Creating pass phrase dialog pipe child "
                             "'%s'", sc->server->pphrase_dialog_path);
                if (ssl_pipe_child_create(p, sc->server->pphrase_dialog_path)
                        != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01966)
                                 "Init: Failed to create pass phrase pipe '%s'",
                                 sc->server->pphrase_dialog_path);
                    PEMerr(PEM_F_PEM_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
                    memset(buf, 0, (unsigned int)bufsize);
                    return (-1);
                }
            }
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01967)
                         "Init: Requesting pass phrase via piped dialog");
        }
        else { /* sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN */
#ifdef WIN32
            PEMerr(PEM_F_PEM_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
            memset(buf, 0, (unsigned int)bufsize);
            return (-1);
#else
            /*
             * stderr has already been redirected to the error_log.
             * rather than attempting to temporarily rehook it to the terminal,
             * we print the prompt to stdout before EVP_read_pw_string turns
             * off tty echo
             */
            apr_file_open_stdout(&writetty, p);

            ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01968)
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
        if (*pnPassPhraseDialog == 1) {
            apr_file_printf(writetty, "%s mod_ssl (Pass Phrase Dialog)\n",
                            AP_SERVER_BASEVERSION);
            apr_file_printf(writetty, "Some of your private key files are encrypted for security reasons.\n");
            apr_file_printf(writetty, "In order to read them you have to provide the pass phrases.\n");
        }
        if (*pbPassPhraseDialogOnce) {
            *pbPassPhraseDialogOnce = FALSE;
            apr_file_printf(writetty, "\n");
            apr_file_printf(writetty, "Server %s (%s)\n", cpVHostID, cpAlgoType);
        }

        /*
         * Emulate the OpenSSL internal pass phrase dialog
         * (see crypto/pem/pem_lib.c:def_callback() for details)
         */
        prompt = "Enter pass phrase:";

        for (;;) {
            apr_file_puts(prompt, writetty);
            if (sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE) {
                i = pipe_get_passwd_cb(buf, bufsize, "", FALSE);
            }
            else { /* sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN */
                i = EVP_read_pw_string(buf, bufsize, "", FALSE);
            }
            if (i != 0) {
                PEMerr(PEM_F_PEM_DEF_CALLBACK,PEM_R_PROBLEMS_GETTING_PASSWORD);
                memset(buf, 0, (unsigned int)bufsize);
                return (-1);
            }
            len = strlen(buf);
            if (len < 1)
                apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase empty (needs to be at least 1 character).\n");
            else
                break;
        }
    }

    /*
     * Filter program
     */
    else if (sc->server->pphrase_dialog_type == SSL_PPTYPE_FILTER) {
        const char *cmd = sc->server->pphrase_dialog_path;
        const char **argv = apr_palloc(p, sizeof(char *) * 4);
        char *result;

        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01969)
                     "Init: Requesting pass phrase from dialog filter "
                     "program (%s)", cmd);

        argv[0] = cmd;
        argv[1] = cpVHostID;
        argv[2] = cpAlgoType;
        argv[3] = NULL;

        result = ssl_util_readfilter(s, p, cmd, argv);
        apr_cpystrn(buf, result, bufsize);
        len = strlen(buf);
    }

    /*
     * Ok, we now have the pass phrase, so give it back
     */
    *cppPassPhraseCur = apr_pstrdup(p, buf);

    /*
     * And return its length to OpenSSL...
     */
    return (len);
}