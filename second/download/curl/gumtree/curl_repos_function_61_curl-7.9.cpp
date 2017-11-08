static
int cert_stuff(struct connectdata *conn,
               char *cert_file,
               char *key_file)
{
  struct SessionHandle *data = conn->data;
  if (cert_file != NULL) {
    SSL *ssl;
    X509 *x509;

    if(data->set.cert_passwd) {
#ifndef HAVE_USERDATA_IN_PWD_CALLBACK
      /*
       * If password has been given, we store that in the global
       * area (*shudder*) for a while:
       */
      strcpy(global_passwd, data->set.cert_passwd);
#else
      /*
       * We set the password in the callback userdata
       */
      SSL_CTX_set_default_passwd_cb_userdata(conn->ssl.ctx, data->set.cert_passwd);
#endif
      /* Set passwd callback: */
      SSL_CTX_set_default_passwd_cb(conn->ssl.ctx, passwd_callback);
    }

    if (SSL_CTX_use_certificate_file(conn->ssl.ctx,
				     cert_file,
				     SSL_FILETYPE_PEM) != 1) {
      failf(data, "unable to set certificate file (wrong password?)\n");
      return(0);
    }
    if (key_file == NULL)
      key_file=cert_file;

    if (SSL_CTX_use_PrivateKey_file(conn->ssl.ctx,
				    key_file,
				    SSL_FILETYPE_PEM) != 1) {
      failf(data, "unable to set public key file\n");
      return(0);
    }
    
    ssl=SSL_new(conn->ssl.ctx);
    x509=SSL_get_certificate(ssl);
    
    if (x509 != NULL)
      EVP_PKEY_copy_parameters(X509_get_pubkey(x509),
			       SSL_get_privatekey(ssl));
    SSL_free(ssl);

    /* If we are using DSA, we can copy the parameters from
     * the private key */
		
    
    /* Now we know that a key and cert have been set against
     * the SSL context */
    if (!SSL_CTX_check_private_key(conn->ssl.ctx)) {
      failf(data, "Private key does not match the certificate public key\n");
      return(0);
    }
#ifndef HAVE_USERDATA_IN_PWD_CALLBACK    
    /* erase it now */
    memset(global_passwd, 0, sizeof(global_passwd));
#endif
  }
  return(1);
}