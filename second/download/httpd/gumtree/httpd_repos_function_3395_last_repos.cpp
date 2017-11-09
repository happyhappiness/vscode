static const char *set_crypto_passphrase(cmd_parms * cmd, void *config, const char *arg)
{
    int arglen = strlen(arg);
    char **argv;
    char *result;
    const char **passphrase;
    session_crypto_dir_conf *dconf = (session_crypto_dir_conf *) config;

    passphrase = apr_array_push(dconf->passphrases);

    if ((arglen > 5) && strncmp(arg, "exec:", 5) == 0) {
        if (apr_tokenize_to_argv(arg+5, &argv, cmd->temp_pool) != APR_SUCCESS) {
            return apr_pstrcat(cmd->pool,
                               "Unable to parse exec arguments from ",
                               arg+5, NULL);
        }
        argv[0] = ap_server_root_relative(cmd->temp_pool, argv[0]);

        if (!argv[0]) {
            return apr_pstrcat(cmd->pool,
                               "Invalid SessionCryptoPassphrase exec location:",
                               arg+5, NULL);
        }
        result = ap_get_exec_line(cmd->pool,
                                  (const char*)argv[0], (const char * const *)argv);

        if(!result) {
            return apr_pstrcat(cmd->pool,
                               "Unable to get bind password from exec of ",
                               arg+5, NULL);
        }
        *passphrase = result;
    }
    else {
        *passphrase = arg;
    }

    dconf->passphrases_set = 1;

    return NULL;
}