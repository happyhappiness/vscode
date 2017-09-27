        if (ticket_key == NULL) {
            /* should never happen, but better safe than sorry */
            return -1;
        }

        memcpy(keyname, ticket_key->key_name, 16);
        RAND_pseudo_bytes(iv, EVP_MAX_IV_LENGTH);
        EVP_EncryptInit_ex(cipher_ctx, EVP_aes_128_cbc(), NULL,
                           ticket_key->aes_key, iv);
        HMAC_Init_ex(hctx, ticket_key->hmac_secret, 16, tlsext_tick_md(), NULL);

        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02289)
                      "TLS session ticket key for %s successfully set, "
