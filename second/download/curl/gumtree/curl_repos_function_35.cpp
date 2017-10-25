int SSL_cert_stuff(struct UrlData *data, 
		   char *cert_file,
		   char *key_file)
{
  if (cert_file != NULL) {
    SSL *ssl;
    X509 *x509;

    if(data->cert_passwd) {
      /*
       * If password has been given, we store that in the global
       * area (*shudder*) for a while:
       */
      strcpy(global_passwd, data->cert_passwd);
      /* Set passwd callback: */
      SSL_CTX_set_default_passwd_cb(data->ctx, passwd_callback);
    }

    if (SSL_CTX_use_certificate_file(data->ctx,
				     cert_file,
				     SSL_FILETYPE_PEM) <= 0) {
      failf(data, "unable to set certificate file (wrong password?)\n");
      return(0);
    }
    if (key_file == NULL)
      key_file=cert_file;

    if (SSL_CTX_use_PrivateKey_file(data->ctx,
				    key_file,
				    SSL_FILETYPE_PEM) <= 0) {
      failf(data, "unable to set public key file\n");
      return(0);
    }
    
    ssl=SSL_new(data->ctx);
    x509=SSL_get_certificate(ssl);
    
    if (x509 != NULL)
      EVP_PKEY_copy_parameters(X509_get_pubkey(x509),
			       SSL_get_privatekey(ssl));
    SSL_free(ssl);

    /* If we are using DSA, we can copy the parameters from
     * the private key */
		
    
    /* Now we know that a key and cert have been set against
     * the SSL context */
    if (!SSL_CTX_check_private_key(data->ctx)) {
      failf(data, "Private key does not match the certificate public key\n");
      return(0);
    }
    
    /* erase it now */
    memset(global_passwd, 0, sizeof(global_passwd));
  }
  return(1);
}