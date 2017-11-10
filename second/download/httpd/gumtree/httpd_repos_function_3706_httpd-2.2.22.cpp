static void sha256_add(apr_crypto_hash_t *h,const void *data,
			  apr_size_t bytes)
    {
    apr__SHA256_Update(h->data,data,bytes);
    }