#define BUILTIN_DIALOG_BACKOFF 2
#define BUILTIN_DIALOG_RETRIES 5

static apr_file_t *writetty = NULL;
static apr_file_t *readtty = NULL;

int ssl_pphrase_Handle_CB(char *, int, int, void *);

static char *pphrase_array_get(apr_array_header_t *arr, int idx)
{
    if ((idx < 0) || (idx >= arr->nelts)) {
        return NULL;
    }

    return ((char **)arr->elts)[idx];
}

apr_status_t ssl_load_encrypted_pkey(server_rec *s, apr_pool_t *p, int idx,
                                     const char *pkey_file,
                                     apr_array_header_t **pphrases)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    const char *key_id = asn1_table_vhost_key(mc, p, sc->vhost_id, idx);
    EVP_PKEY *pPrivateKey = NULL;
    ssl_asn1_t *asn1;
    unsigned char *ucp;
    long int length;
    BOOL bReadable;
    int nPassPhrase = (*pphrases)->nelts;
    int nPassPhraseRetry = 0;
    apr_time_t pkey_mtime = 0;
    apr_status_t rv;
    pphrase_cb_arg_t ppcb_arg;

    if (!pkey_file) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02573)
                      "Init: No private key specified for %s", key_id);
         return ssl_die(s);
    }
    else if ((rv = exists_and_readable(pkey_file, p, &pkey_mtime))
             != APR_SUCCESS ) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02574)
                      "Init: Can't open server private key file %s", pkey_file);
         return ssl_die(s);
    }

    ppcb_arg.s                     = s;
    ppcb_arg.p                     = p;
    ppcb_arg.aPassPhrase           = *pphrases;
    ppcb_arg.nPassPhraseCur        = 0;
    ppcb_arg.cpPassPhraseCur       = NULL;
    ppcb_arg.nPassPhraseDialog     = 0;
    ppcb_arg.nPassPhraseDialogCur  = 0;
    ppcb_arg.bPassPhraseDialogOnce = TRUE;
    ppcb_arg.key_id                = key_id;
    ppcb_arg.pkey_file             = pkey_file;

    /*
     * if the private key is encrypted and SSLPassPhraseDialog
     * is configured to "builtin" it isn't possible to prompt for
     * a password after httpd has detached from the tty.
     * in this case if we already have a private key and the
     * file name/mtime hasn't changed, then reuse the existing key.
     * we also reuse existing private keys that were encrypted for
     * exec: and pipe: dialogs to minimize chances to snoop the
     * password.  that and pipe: dialogs might prompt the user
     * for password, which on win32 for example could happen 4
     * times at startup.  twice for each child and twice within
     * each since apache "restarts itself" on startup.
     * of course this will not work for the builtin dialog if
     * the server was started without LoadModule ssl_module
     * configured, then restarted with it configured.
     * but we fall through with a chance of success if the key
     * is not encrypted or can be handled via exec or pipe dialog.
     * and in the case of fallthrough, pkey_mtime and isatty()
     * are used to give a better idea as to what failed.
     */
    if (pkey_mtime) {
        ssl_asn1_t *asn1 = ssl_asn1_table_get(mc->tPrivateKey, key_id);
        if (asn1 && (asn1->source_mtime == pkey_mtime)) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02575)
                         "Reusing existing private key from %s on restart",
                         ppcb_arg.pkey_file);
            return APR_SUCCESS;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02576)
                 "Attempting to load encrypted (?) private key %s", key_id);

    for (;;) {
        /*
         * Try to read the private key file with the help of
         * the callback function which serves the pass
         * phrases to OpenSSL
         */

        ppcb_arg.cpPassPhraseCur = NULL;

        /* Ensure that the error stack is empty; some SSL
         * functions will fail spuriously if the error stack
         * is not empty. */
        ERR_clear_error();

        bReadable = ((pPrivateKey = SSL_read_PrivateKey(ppcb_arg.pkey_file,
                     NULL, ssl_pphrase_Handle_CB, &ppcb_arg)) != NULL ?
                     TRUE : FALSE);

        /*
         * when the private key file now was readable,
         * it's fine and we go out of the loop
         */
        if (bReadable)
           break;

        /*
         * when we have more remembered pass phrases
         * try to reuse these first.
         */
        if (ppcb_arg.nPassPhraseCur < nPassPhrase) {
            ppcb_arg.nPassPhraseCur++;
            continue;
        }

        /*
         * else it's not readable and we have no more
         * remembered pass phrases. Then this has to mean
         * that the callback function popped up the dialog
         * but a wrong pass phrase was entered.  We give the
         * user (but not the dialog program) a few more
         * chances...
         */
#ifndef WIN32
        if ((sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN
             || sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE)
#else
        if (sc->server->pphrase_dialog_type == SSL_PPTYPE_PIPE
#endif
            && ppcb_arg.cpPassPhraseCur != NULL
            && nPassPhraseRetry < BUILTIN_DIALOG_RETRIES ) {
            apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect "
                    "(%d more retr%s permitted).\n",
                    (BUILTIN_DIALOG_RETRIES-nPassPhraseRetry),
                    (BUILTIN_DIALOG_RETRIES-nPassPhraseRetry) == 1 ? "y" : "ies");
            nPassPhraseRetry++;
            if (nPassPhraseRetry > BUILTIN_DIALOG_BACKOFF)
                apr_sleep((nPassPhraseRetry-BUILTIN_DIALOG_BACKOFF)
                            * 5 * APR_USEC_PER_SEC);
            continue;
        }
#ifdef WIN32
        if (sc->server->pphrase_dialog_type == SSL_PPTYPE_BUILTIN) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02577)
                         "Init: SSLPassPhraseDialog builtin is not "
                         "supported on Win32 (key file "
                         "%s)", ppcb_arg.pkey_file);
            return ssl_die(s);
        }
#endif /* WIN32 */

        /*
         * Ok, anything else now means a fatal error.
         */
        if (ppcb_arg.cpPassPhraseCur == NULL) {
            if (ppcb_arg.nPassPhraseDialogCur && pkey_mtime &&
                !isatty(fileno(stdout))) /* XXX: apr_isatty() */
            {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             s, APLOGNO(02578)
                             "Init: Unable to read pass phrase "
                             "[Hint: key introduced or changed "
                             "before restart?]");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             s, APLOGNO(02579) "Init: Private key not found");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            }
            if (writetty) {
                apr_file_printf(writetty, "Apache:mod_ssl:Error: Private key not found.\n");
                apr_file_printf(writetty, "**Stopped\n");
            }
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02580)
                         "Init: Pass phrase incorrect for key %s",
                         key_id);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);

            if (writetty) {
                apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect.\n");
                apr_file_printf(writetty, "**Stopped\n");
            }
        }
        return ssl_die(s);
    }

    if (pPrivateKey == NULL) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02581)
                     "Init: Unable to read server private key from file %s",
                     ppcb_arg.pkey_file);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        return ssl_die(s);
    }

    /*
     * Log the type of reading
     */
    if (ppcb_arg.nPassPhraseDialogCur == 0) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02582)
                     "unencrypted %s private key - pass phrase not "
                     "required", key_id);
    }
    else {
        if (ppcb_arg.cpPassPhraseCur != NULL) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                         s, APLOGNO(02583)
                         "encrypted %s private key - pass phrase "
                         "requested", key_id);
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                         s, APLOGNO(02584)
                         "encrypted %s private key - pass phrase"
                         " reused", key_id);
        }
    }

    /*
     * Ok, when we have one more pass phrase store it
     */
    if (ppcb_arg.cpPassPhraseCur != NULL) {
        *(const char **)apr_array_push(ppcb_arg.aPassPhrase) =
            ppcb_arg.cpPassPhraseCur;
        nPassPhrase++;
    }

    /*
     * Insert private key into the global module configuration
     * (we convert it to a stand-alone DER byte sequence
     * because the SSL library uses static variables inside a
     * RSA structure which do not survive DSO reloads!)
     */
    length = i2d_PrivateKey(pPrivateKey, NULL);
    ucp = ssl_asn1_table_set(mc->tPrivateKey, key_id, length);
    (void)i2d_PrivateKey(pPrivateKey, &ucp); /* 2nd arg increments */

    if (ppcb_arg.nPassPhraseDialogCur != 0) {
        /* remember mtime of encrypted keys */
        asn1 = ssl_asn1_table_get(mc->tPrivateKey, key_id);
        asn1->source_mtime = pkey_mtime;
    }

    /*
     * Free the private key structure
     */
    EVP_PKEY_free(pPrivateKey);

    /*
     * Let the user know when we're successful.
     */
    if ((ppcb_arg.nPassPhraseDialog > 0) &&
        (ppcb_arg.cpPassPhraseCur != NULL)) {
        if (writetty) {
            apr_file_printf(writetty, "\n"
                            "OK: Pass Phrase Dialog successful.\n");
        }
    }

    /* Close the pipes if they were opened
     */
    if (readtty) {
        apr_file_close(readtty);
        apr_file_close(writetty);
        readtty = writetty = NULL;
    }

    return APR_SUCCESS;
}

static apr_status_t ssl_pipe_child_create(apr_pool_t *p, const char *progname)
{
    /* Child process code for 'ErrorLog "|..."';
     * may want a common framework for this, since I expect it will
