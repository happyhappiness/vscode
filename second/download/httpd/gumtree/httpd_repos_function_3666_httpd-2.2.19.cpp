static void sha256_finish(apr_crypto_hash_t *h,unsigned char *result)
    {
    apr__SHA256_Final(result,h->data);
    }