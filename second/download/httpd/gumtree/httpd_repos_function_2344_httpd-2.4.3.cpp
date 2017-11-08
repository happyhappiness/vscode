static void *create_session_crypto_dir_config(apr_pool_t * p, char *dummy)
{
    session_crypto_dir_conf *new =
    (session_crypto_dir_conf *) apr_pcalloc(p, sizeof(session_crypto_dir_conf));

    new->passphrases = apr_array_make(p, 10, sizeof(char *));

    /* default cipher AES256-SHA */
    new->cipher = "aes256";

    return (void *) new;
}