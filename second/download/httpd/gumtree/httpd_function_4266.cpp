int ssl_callback_SessionTicket(SSL *ssl,
                               unsigned char *keyname,
                               unsigned char *iv,
                               EVP_CIPHER_CTX *cipher_ctx,
                               HMAC_CTX *hctx,
                               int mode)
{
    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
    server_rec *s = mySrvFromConn(c);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    SSLConnRec *sslconn = myConnConfig(c);
    modssl_ctx_t *mctx = myCtxConfig(sslconn, sc);
    modssl_ticket_key_t *ticket_key = mctx->ticket_key;

    if (mode == 1) {
        /* 
         * OpenSSL is asking for a key for encrypting a ticket,
         * see s3_srvr.c:ssl3_send_newsession_ticket()
         */

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
                      "creating new session ticket", sc->vhost_id);

        return 0;
    }
    else if (mode == 0) {
        /* 
         * OpenSSL is asking for the decryption key,
         * see t1_lib.c:tls_decrypt_ticket()
         */

        /* check key name */
        if (ticket_key == NULL || memcmp(keyname, ticket_key->key_name, 16)) {
            return 0;
        }

        EVP_DecryptInit_ex(cipher_ctx, EVP_aes_128_cbc(), NULL,
                           ticket_key->aes_key, iv);
        HMAC_Init_ex(hctx, ticket_key->hmac_secret, 16, tlsext_tick_md(), NULL);

        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02290)
                      "TLS session ticket key for %s successfully set, "
                      "decrypting existing session ticket", sc->vhost_id);

        return 1;
    }

    /* OpenSSL is not expected to call us with modes other than 1 or 0 */
    return -1;
}