static const char *set_crypto_cipher(cmd_parms * cmd, void *config, const char *cipher)
{
    session_crypto_dir_conf *dconf = (session_crypto_dir_conf *) config;

    dconf->cipher = cipher;
    dconf->cipher_set = 1;

    return NULL;
}