static
int cert_stuff(struct connectdata *conn,
               SSL_CTX* ctx,
               char *cert_file,
               const char *cert_type,
               char *key_file,
               const char *key_type)
{
  struct SessionHandle *data = conn->data;
  int file_type;

  if(cert_file != NULL) {
    SSL *ssl;
    X509 *x509;
    int cert_done = 0;

    if(data->set.key_passwd) {
#ifndef HAVE_USERDATA_IN_PWD_CALLBACK
      /*
       * If password has been given, we store that in the global
       * area (*shudder*) for a while:
       */
      size_t len = strlen(data->set.key_passwd);
      if(len < sizeof(global_passwd))
        memcpy(global_passwd, data->set.key_passwd, len+1);
#else
      /*
       * We set the password in the callback userdata
       */
      SSL_CTX_set_default_passwd_cb_userdata(ctx,
                                             data->set.key_passwd);
#endif
      /* Set passwd callback: */
      SSL_CTX_set_default_passwd_cb(ctx, passwd_callback);
    }

    file_type = do_file_type(cert_type);

#define SSL_CLIENT_CERT_ERR \
    "unable to use client certificate (no key found or wrong pass phrase?)"

    switch(file_type) {
    case SSL_FILETYPE_PEM:
      /* SSL_CTX_use_certificate_chain_file() only works on PEM files */
      if(SSL_CTX_use_certificate_chain_file(ctx,
                                            cert_file) != 1) {
        failf(data, SSL_CLIENT_CERT_ERR);
        return 0;
      }
      break;

    case SSL_FILETYPE_ASN1:
      /* SSL_CTX_use_certificate_file() works with either PEM or ASN1, but
         we use the case above for PEM so this can only be performed with
         ASN1 files. */
      if(SSL_CTX_use_certificate_file(ctx,
                                      cert_file,
                                      file_type) != 1) {
        failf(data, SSL_CLIENT_CERT_ERR);
        return 0;
      }
      break;
    case SSL_FILETYPE_ENGINE:
      failf(data, "file type ENG for certificate not implemented");
      return 0;

    case SSL_FILETYPE_PKCS12:
    {
#ifdef HAVE_PKCS12_SUPPORT
      FILE *f;
      PKCS12 *p12;
      EVP_PKEY *pri;

      f = fopen(cert_file,"rb");
      if (!f) {
        failf(data, "could not open PKCS12 file '%s'", cert_file);
        return 0;
      }
      p12 = d2i_PKCS12_fp(f, NULL);
      fclose(f);

      PKCS12_PBE_add();

      if (!PKCS12_parse(p12, data->set.key_passwd, &pri, &x509, NULL)) {
        failf(data,
              "could not parse PKCS12 file, check password, OpenSSL error %s",
              ERR_error_string(ERR_get_error(), NULL) );
        return 0;
      }

      PKCS12_free(p12);

      if(SSL_CTX_use_certificate(ctx, x509) != 1) {
        failf(data, SSL_CLIENT_CERT_ERR);
        EVP_PKEY_free(pri);
        X509_free(x509);
        return 0;
      }

      if(SSL_CTX_use_PrivateKey(ctx, pri) != 1) {
        failf(data, "unable to use private key from PKCS12 file '%s'",
              cert_file);
        EVP_PKEY_free(pri);
        X509_free(x509);
        return 0;
      }

      EVP_PKEY_free(pri);
      X509_free(x509);
      cert_done = 1;
      break;
#else
      failf(data, "file type P12 for certificate not supported");
      return 0;
#endif
    }
    default:
      failf(data, "not supported file type '%s' for certificate", cert_type);
      return 0;
    }

    file_type = do_file_type(key_type);

    switch(file_type) {
    case SSL_FILETYPE_PEM:
      if(cert_done)
        break;
      if(key_file == NULL)
        /* cert & key can only be in PEM case in the same file */
        key_file=cert_file;
    case SSL_FILETYPE_ASN1:
      if(SSL_CTX_use_PrivateKey_file(ctx, key_file, file_type) != 1) {
        failf(data, "unable to set private key file: '%s' type %s\n",
              key_file, key_type?key_type:"PEM");
        return 0;
      }
      break;
    case SSL_FILETYPE_ENGINE:
#ifdef HAVE_OPENSSL_ENGINE_H
      {                         /* XXXX still needs some work */
        EVP_PKEY *priv_key = NULL;
        if(conn && conn->data && conn->data->state.engine) {
#ifdef HAVE_ENGINE_LOAD_FOUR_ARGS
          UI_METHOD *ui_method = UI_OpenSSL();
#endif
          if(!key_file || !key_file[0]) {
            failf(data, "no key set to load from crypto engine\n");
            return 0;
          }
          /* the typecast below was added to please mingw32 */
          priv_key = (EVP_PKEY *)
            ENGINE_load_private_key(conn->data->state.engine,key_file,
#ifdef HAVE_ENGINE_LOAD_FOUR_ARGS
                                    ui_method,
#endif
                                    data->set.key_passwd);
          if(!priv_key) {
            failf(data, "failed to load private key from crypto engine\n");
            return 0;
          }
          if(SSL_CTX_use_PrivateKey(ctx, priv_key) != 1) {
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
      break;
#else
      failf(data, "file type ENG for private key not supported\n");
      return 0;
#endif
    case SSL_FILETYPE_PKCS12:
      if(!cert_done) {
        failf(data, "file type P12 for private key not supported\n");
        return 0;
      }
      break;
    default:
      failf(data, "not supported file type for private key\n");
      return 0;
    }

    ssl=SSL_new(ctx);
    if (NULL == ssl) {
      failf(data,"unable to create an SSL structure\n");
      return 0;
    }

    x509=SSL_get_certificate(ssl);

    /* This version was provided by Evan Jordan and is supposed to not
       leak memory as the previous version: */
    if(x509 != NULL) {
      EVP_PKEY *pktmp = X509_get_pubkey(x509);
      EVP_PKEY_copy_parameters(pktmp,SSL_get_privatekey(ssl));
      EVP_PKEY_free(pktmp);
    }

    SSL_free(ssl);

    /* If we are using DSA, we can copy the parameters from
     * the private key */


    /* Now we know that a key and cert have been set against
     * the SSL context */
    if(!SSL_CTX_check_private_key(ctx)) {
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