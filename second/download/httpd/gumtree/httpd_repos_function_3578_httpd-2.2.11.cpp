static void sha256_init(apr_crypto_hash_t *h)
    {
    apr__SHA256_Init(h->data);
    }