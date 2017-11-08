static void sha256_add(apr_crypto_hash_t *h,const void *data,
			  apr_size_t bytes)
    {
    SHA256_Update(h->data,data,bytes);
    }