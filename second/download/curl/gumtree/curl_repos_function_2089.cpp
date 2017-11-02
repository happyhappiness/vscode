static
int cert_stuff(struct connectdata *conn,
               SSL_CTX* ctx,
               char *cert_file,
               const char *cert_type,
               char *key_file,
               const char *key_type)
{
  struct SessionHandle *data = conn->data;

  int file_type = do_file_type(cert_type);

  if(cert_file || (file_type == SSL_FILETYPE_ENGINE)) {
    SSL *ssl;
    X509 *x509;
    int cert_done = 0;

    if(data->set.str[STRING_KEY_PASSWD]) {
#ifndef HAVE_USERDATA_IN_PWD_CALLBACK
      /*
       * If password has been given, we store that in the global
       * area (*shudder*) for a while:
       */
      size_t len = strlen(data->set.str[STRING_KEY_PASSWD]);
      if(len < sizeof(global_passwd))
        memcpy(global_passwd, data->set.str[STRING_KEY_PASSWD], len+1);
      else
        global_passwd[0] = '\0';
#else
      /*
       * We set the password in the callback userdata
       */
      SSL_CTX_set_default_passwd_cb_userdata(ctx,
                                             data->set.str[STRING_KEY_PASSWD]);
#endif
      /* Set passwd callback: */
      SSL_CTX_set_default_passwd_cb(ctx, passwd_callback);
    }


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
#if defined(HAVE_OPENSSL_ENGINE_H) && defined(ENGINE_CTRL_GET_CMD_FROM_NAME)
      {
        if(data->state.engine) {
          const char *cmd_name = "LOAD_CERT_CTRL";
          struct {
            const char *cert_id;
            X509 *cert;
          } params;

          params.cert_id = cert_file;
          params.cert = NULL;

          /* Does the engine supports LOAD_CERT_CTRL ? */
          if(!ENGINE_ctrl(data->state.engine, ENGINE_CTRL_GET_CMD_FROM_NAME,
                          0, (void *)cmd_name, NULL)) {
            failf(data, "ssl engine does not support loading certificates");
            return 0;
          }

          /* Load the certificate from the engine */
          if(!ENGINE_ctrl_cmd(data->state.engine, cmd_name,
                              0, &params, NULL, 1)) {
            failf(data, "ssl engine cannot load client cert with id"
                  " '%s' [%s]", cert_file,
                  ERR_error_string(ERR_get_error(), NULL));
            return 0;
          }

          if(!params.cert) {
            failf(data, "ssl engine didn't initialized the certificate "
                  "properly.");
            return 0;
          }

          if(SSL_CTX_use_certificate(ctx, params.cert) != 1) {
            failf(data, "unable to set client certificate");
            X509_free(params.cert);
            return 0;
          }
          X509_free(params.cert); /* we don't need the handle any more... */
        }
        else {
          failf(data, "crypto engine not set, can't load certificate");
          return 0;
        }
      }
      break;
#else
      failf(data, "file type ENG for certificate not implemented");
      return 0;
#endif

    case SSL_FILETYPE_PKCS12:
    {
#ifdef HAVE_PKCS12_SUPPORT
      FILE *f;
      PKCS12 *p12;
      EVP_PKEY *pri;
      STACK_OF(X509) *ca = NULL;
      int i;

      f = fopen(cert_file,"rb");
      if(!f) {
        failf(data, "could not open PKCS12 file '%s'", cert_file);
        return 0;
      }
      p12 = d2i_PKCS12_fp(f, NULL);
      fclose(f);

      if(!p12) {
        failf(data, "error reading PKCS12 file '%s'", cert_file );
        return 0;
      }

      PKCS12_PBE_add();

      if(!PKCS12_parse(p12, data->set.str[STRING_KEY_PASSWD], &pri, &x509,
                       &ca)) {
        failf(data,
              "could not parse PKCS12 file, check password, OpenSSL error %s",
              ERR_error_string(ERR_get_error(), NULL) );
        PKCS12_free(p12);
        return 0;
      }

      PKCS12_free(p12);

      if(SSL_CTX_use_certificate(ctx, x509) != 1) {
        failf(data, SSL_CLIENT_CERT_ERR);
        goto fail;
      }

      if(SSL_CTX_use_PrivateKey(ctx, pri) != 1) {
        failf(data, "unable to use private key from PKCS12 file '%s'",
              cert_file);
        goto fail;
      }

      if(!SSL_CTX_check_private_key (ctx)) {
        failf(data, "private key from PKCS12 file '%s' "
              "does not match certificate in same file", cert_file);
        goto fail;
      }
      /* Set Certificate Verification chain */
      if(ca && sk_X509_num(ca)) {
        for(i = 0; i < sk_X509_num(ca); i++) {
          /*
           * Note that sk_X509_pop() is used below to make sure the cert is
           * removed from the stack properly before getting passed to
           * SSL_CTX_add_extra_chain_cert(). Previously we used
           * sk_X509_value() instead, but then we'd clean it in the subsequent
           * sk_X509_pop_free() call.
           */
          X509 *x = sk_X509_pop(ca);
          if(!SSL_CTX_add_extra_chain_cert(ctx, x)) {
            failf(data, "cannot add certificate to certificate chain");
            goto fail;
          }
          /* SSL_CTX_add_client_CA() seems to work with either sk_* function,
           * presumably because it duplicates what we pass to it.
           */
          if(!SSL_CTX_add_client_CA(ctx, x)) {
            failf(data, "cannot add certificate to client CA list");
            goto fail;
          }
        }
      }

      cert_done = 1;
  fail:
      EVP_PKEY_free(pri);
      X509_free(x509);
      sk_X509_pop_free(ca, X509_free);

      if(!cert_done)
        return 0; /* failure! */
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
      if(!key_file)
        /* cert & key can only be in PEM case in the same file */
        key_file=cert_file;
    case SSL_FILETYPE_ASN1:
      if(SSL_CTX_use_PrivateKey_file(ctx, key_file, file_type) != 1) {
        failf(data, "unable to set private key file: '%s' type %s",
              key_file, key_type?key_type:"PEM");
        return 0;
      }
      break;
    case SSL_FILETYPE_ENGINE:
#ifdef HAVE_OPENSSL_ENGINE_H
      {                         /* XXXX still needs some work */
        EVP_PKEY *priv_key = NULL;
        if(data->state.engine) {
#ifdef HAVE_ENGINE_LOAD_FOUR_ARGS
          UI_METHOD *ui_method =
            UI_create_method((char *)"cURL user interface");
          if(!ui_method) {
            failf(data, "unable do create OpenSSL user-interface method");
            return 0;
          }
          UI_method_set_opener(ui_method, UI_method_get_opener(UI_OpenSSL()));
          UI_method_set_closer(ui_method, UI_method_get_closer(UI_OpenSSL()));
          UI_method_set_reader(ui_method, ssl_ui_reader);
          UI_method_set_writer(ui_method, ssl_ui_writer);
#endif
          /* the typecast below was added to please mingw32 */
          priv_key = (EVP_PKEY *)
            ENGINE_load_private_key(data->state.engine,key_file,
#ifdef HAVE_ENGINE_LOAD_FOUR_ARGS
                                    ui_method,
#endif
                                    data->set.str[STRING_KEY_PASSWD]);
#ifdef HAVE_ENGINE_LOAD_FOUR_ARGS
          UI_destroy_method(ui_method);
#endif
          if(!priv_key) {
            failf(data, "failed to load private key from crypto engine");
            return 0;
          }
          if(SSL_CTX_use_PrivateKey(ctx, priv_key) != 1) {
            failf(data, "unable to set private key");
            EVP_PKEY_free(priv_key);
            return 0;
          }
          EVP_PKEY_free(priv_key);  /* we don't need the handle any more... */
        }
        else {
          failf(data, "crypto engine not set, can't load private key");
          return 0;
        }
      }
      break;
#else
      failf(data, "file type ENG for private key not supported");
      return 0;
#endif
    case SSL_FILETYPE_PKCS12:
      if(!cert_done) {
        failf(data, "file type P12 for private key not supported");
        return 0;
      }
      break;
    default:
      failf(data, "not supported file type for private key");
      return 0;
    }

    ssl=SSL_new(ctx);
    if(!ssl) {
      failf(data,"unable to create an SSL structure");
      return 0;
    }

    x509=SSL_get_certificate(ssl);

    /* This version was provided by Evan Jordan and is supposed to not
       leak memory as the previous version: */
    if(x509) {
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
      return 0;
    }
#ifndef HAVE_USERDATA_IN_PWD_CALLBACK
    /* erase it now */
    memset(global_passwd, 0, sizeof(global_passwd));
#endif
  }
  return 1;
}