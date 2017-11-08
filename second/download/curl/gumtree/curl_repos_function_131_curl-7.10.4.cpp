static
int cert_stuff(struct connectdata *conn,
               char *cert_file,
               const char *cert_type,
               char *key_file,
               const char *key_type)
{
  struct SessionHandle *data = conn->data;
  int file_type;

  if (cert_file != NULL) {
    SSL *ssl;
    X509 *x509;

    if(data->set.key_passwd) {
#ifndef HAVE_USERDATA_IN_PWD_CALLBACK
      /*
       * If password has been given, we store that in the global
       * area (*shudder*) for a while:
       */
      strcpy(global_passwd, data->set.key_passwd);
#else
      /*
       * We set the password in the callback userdata
       */
      SSL_CTX_set_default_passwd_cb_userdata(conn->ssl.ctx,
                                             data->set.key_passwd);
#endif
      /* Set passwd callback: */
      SSL_CTX_set_default_passwd_cb(conn->ssl.ctx, passwd_callback);
    }

    file_type = do_file_type(cert_type);

    switch(file_type) {
    case SSL_FILETYPE_PEM:
      /* SSL_CTX_use_certificate_chain_file() only works on PEM files */
      if (SSL_CTX_use_certificate_chain_file(conn->ssl.ctx,
                                             cert_file) != 1) {
        failf(data, "unable to set certificate file (wrong password?)");
        return 0;
      }
      break;

    case SSL_FILETYPE_ASN1:
      /* SSL_CTX_use_certificate_file() works with either PEM or ASN1, but
         we use the case above for PEM so this can only be performed with
         ASN1 files. */
      if (SSL_CTX_use_certificate_file(conn->ssl.ctx,
                                       cert_file,
                                       file_type) != 1) {
        failf(data, "unable to set certificate file (wrong password?)");
        return 0;
      }
      break;
    case SSL_FILETYPE_ENGINE:
      failf(data, "file type ENG for certificate not implemented");
      return 0;

    default:
      failf(data, "not supported file type '%s' for certificate", cert_type);
      return 0;
    }

    file_type = do_file_type(key_type);

    switch(file_type) {
    case SSL_FILETYPE_PEM:
      if (key_file == NULL)
        /* cert & key can only be in PEM case in the same file */
        key_file=cert_file;
    case SSL_FILETYPE_ASN1:
      if (SSL_CTX_use_PrivateKey_file(conn->ssl.ctx,
                                      key_file,
                                      file_type) != 1) {
        failf(data, "unable to set private key file: '%s' type %s\n",
              key_file, key_type?key_type:"PEM");
        return 0;
      }
      break;
    case SSL_FILETYPE_ENGINE:
#ifdef HAVE_OPENSSL_ENGINE_H
      {                         /* XXXX still needs some work */
        EVP_PKEY *priv_key = NULL;
        if (conn && conn->data && conn->data->engine) {
#ifdef HAVE_ENGINE_LOAD_FOUR_ARGS
          UI_METHOD *ui_method = UI_OpenSSL();
#endif
          if (!key_file || !key_file[0]) {
            failf(data, "no key set to load from crypto engine\n");
            return 0;
          }
          priv_key = ENGINE_load_private_key(conn->data->engine,key_file,
#ifdef HAVE_ENGINE_LOAD_FOUR_ARGS
                                             ui_method,
#endif
                                             data->set.key_passwd);
          if (!priv_key) {
            failf(data, "failed to load private key from crypto engine\n");
            return 0;
          }
          if (SSL_CTX_use_PrivateKey(conn->ssl.ctx, priv_key) != 1) {
            failf(data, "unable to set private key\n");
            EVP_PKEY_free(priv_key);
            return 0;
          }
          EVP_PKEY_free(priv_key);  /* we don't need the handle any more... */
        }
        else {
          failf(data, "crypto engine not set, can't load private key\n");
          return 0;
        }
      }
#else
      failf(data, "file type ENG for private key not supported\n");
      return 0;
#endif
      break;
    default:
      failf(data, "not supported file type for private key\n");
      return 0;
    }

    ssl=SSL_new(conn->ssl.ctx);
    x509=SSL_get_certificate(ssl);

    /* This version was provided by Evan Jordan and is supposed to not
       leak memory as the previous version: */
    if (x509 != NULL) {
      EVP_PKEY *pktmp = X509_get_pubkey(x509);
      EVP_PKEY_copy_parameters(pktmp,SSL_get_privatekey(ssl));
      EVP_PKEY_free(pktmp);
    }

    SSL_free(ssl);

    /* If we are using DSA, we can copy the parameters from
     * the private key */
		
    
    /* Now we know that a key and cert have been set against
     * the SSL context */
    if (!SSL_CTX_check_private_key(conn->ssl.ctx)) {
      failf(data, "Private key does not match the certificate public key");
      return(0);
    }
#ifndef HAVE_USERDATA_IN_PWD_CALLBACK    
    /* erase it now */
    memset(global_passwd, 0, sizeof(global_passwd));
#endif
  }
  return(1);
}