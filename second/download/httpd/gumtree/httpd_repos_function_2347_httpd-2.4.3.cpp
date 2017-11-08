static const char *set_crypto_passphrase(cmd_parms * cmd, void *config, const char *arg)
{
    const char **passphrase;
    session_crypto_dir_conf *dconf = (session_crypto_dir_conf *) config;

    passphrase = apr_array_push(dconf->passphrases);
    *passphrase = arg;
    dconf->passphrases_set = 1;

    return NULL;
}