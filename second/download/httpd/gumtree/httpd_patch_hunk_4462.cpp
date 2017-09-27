     apr_status_t res;
     apr_crypto_key_t *key = NULL;
     apr_size_t ivSize = 0;
     apr_crypto_block_t *block = NULL;
     unsigned char *encrypt = NULL;
     unsigned char *combined = NULL;
-    apr_size_t encryptlen, tlen;
+    apr_size_t encryptlen, tlen, combinedlen;
     char *base64;
     apr_size_t blockSize = 0;
     const unsigned char *iv = NULL;
     apr_uuid_t salt;
     apr_crypto_block_key_type_e *cipher;
     const char *passphrase;
-
-    /* by default, return an empty string */
-    *out = "";
-
-    /* don't attempt to encrypt an empty string, trying to do so causes a segfault */
-    if (!in || !*in) {
-        return APR_SUCCESS;
-    }
+    apr_size_t passlen;
 
     /* use a uuid as a salt value, and prepend it to our result */
     apr_uuid_get(&salt);
     res = crypt_init(r, f, &cipher, dconf);
     if (res != APR_SUCCESS) {
         return res;
     }
 
     /* encrypt using the first passphrase in the list */
-    passphrase = APR_ARRAY_IDX(dconf->passphrases, 0, char *);
-    res = apr_crypto_passphrase(&key, &ivSize, passphrase,
-            strlen(passphrase),
+    passphrase = APR_ARRAY_IDX(dconf->passphrases, 0, const char *);
+    passlen = strlen(passphrase);
+    res = apr_crypto_passphrase(&key, &ivSize, passphrase, passlen,
             (unsigned char *) (&salt), sizeof(apr_uuid_t),
             *cipher, APR_MODE_CBC, 1, 4096, f, r->pool);
     if (APR_STATUS_IS_ENOKEY(res)) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01825)
                 "the passphrase '%s' was empty", passphrase);
     }
