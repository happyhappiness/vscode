static void *merge_session_crypto_dir_config(apr_pool_t * p, void *basev, void *addv)
{
    session_crypto_dir_conf *new = (session_crypto_dir_conf *) apr_pcalloc(p, sizeof(session_crypto_dir_conf));
    session_crypto_dir_conf *add = (session_crypto_dir_conf *) addv;
    session_crypto_dir_conf *base = (session_crypto_dir_conf *) basev;

    new->passphrases = (add->passphrases_set == 0) ? base->passphrases : add->passphrases;
    new->passphrases_set = add->passphrases_set || base->passphrases_set;
    new->cipher = (add->cipher_set == 0) ? base->cipher : add->cipher;
    new->cipher_set = add->cipher_set || base->cipher_set;

    return new;
}