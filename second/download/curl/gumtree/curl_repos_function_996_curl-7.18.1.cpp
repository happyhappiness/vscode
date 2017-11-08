CURLcode Curl_nss_connect(struct connectdata * conn, int sockindex)
{
  PRInt32 err;
  PRFileDesc *model = NULL;
  PRBool ssl2, ssl3, tlsv1;
  struct SessionHandle *data = conn->data;
  curl_socket_t sockfd = conn->sock[sockindex];
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  SECStatus rv;
#ifdef HAVE_PK11_CREATEGENERICOBJECT
  char *configstring = NULL;
#endif
  char *certDir = NULL;
  int curlerr;

  curlerr = CURLE_SSL_CONNECT_ERROR;

  /* FIXME. NSS doesn't support multiple databases open at the same time. */
  if(!initialized) {
    initialized = 1;

    certDir = getenv("SSL_DIR"); /* Look in $SSL_DIR */

    if(!certDir) {
      struct stat st;

      if(stat(SSL_DIR, &st) == 0)
        if(S_ISDIR(st.st_mode)) {
          certDir = (char *)SSL_DIR;
        }
    }

    if(!certDir) {
      rv = NSS_NoDB_Init(NULL);
    }
    else {
      rv = NSS_Initialize(certDir, NULL, NULL, "secmod.db",
                          NSS_INIT_READONLY);
    }
    if(rv != SECSuccess) {
      infof(conn->data, "Unable to initialize NSS database\n");
      curlerr = CURLE_SSL_CACERT_BADFILE;
      goto error;
    }

    NSS_SetDomesticPolicy();

#ifdef HAVE_PK11_CREATEGENERICOBJECT
    configstring = (char *)malloc(PATH_MAX);

    PR_snprintf(configstring, PATH_MAX, "library=%s name=PEM", pem_library);

    mod = SECMOD_LoadUserModule(configstring, NULL, PR_FALSE);
    free(configstring);
    if(!mod || !mod->loaded) {
      if(mod) {
        SECMOD_DestroyModule(mod);
        mod = NULL;
      }
      infof(data, "WARNING: failed to load NSS PEM library %s. Using OpenSSL "
            "PEM certificates will not work.\n", pem_library);
    }
#endif
  }

  model = PR_NewTCPSocket();
  if(!model)
    goto error;
  model = SSL_ImportFD(NULL, model);

  if(SSL_OptionSet(model, SSL_SECURITY, PR_TRUE) != SECSuccess)
    goto error;
  if(SSL_OptionSet(model, SSL_HANDSHAKE_AS_SERVER, PR_FALSE) != SECSuccess)
    goto error;
  if(SSL_OptionSet(model, SSL_HANDSHAKE_AS_CLIENT, PR_TRUE) != SECSuccess)
    goto error;

  ssl2 = ssl3 = tlsv1 = PR_FALSE;

  switch (data->set.ssl.version) {
  default:
  case CURL_SSLVERSION_DEFAULT:
    ssl3 = tlsv1 = PR_TRUE;
    break;
  case CURL_SSLVERSION_TLSv1:
    tlsv1 = PR_TRUE;
    break;
  case CURL_SSLVERSION_SSLv2:
    ssl2 = PR_TRUE;
    break;
  case CURL_SSLVERSION_SSLv3:
    ssl3 = PR_TRUE;
    break;
  }

  if(SSL_OptionSet(model, SSL_ENABLE_SSL2, ssl2) != SECSuccess)
    goto error;
  if(SSL_OptionSet(model, SSL_ENABLE_SSL3, ssl3) != SECSuccess)
    goto error;
  if(SSL_OptionSet(model, SSL_ENABLE_TLS, tlsv1) != SECSuccess)
    goto error;

  if(SSL_OptionSet(model, SSL_V2_COMPATIBLE_HELLO, ssl2) != SECSuccess)
    goto error;

  if(data->set.ssl.cipher_list) {
    if(set_ciphers(data, model, data->set.ssl.cipher_list) != SECSuccess) {
      curlerr = CURLE_SSL_CIPHER;
      goto error;
    }
  }

  data->set.ssl.certverifyresult=0; /* not checked yet */
  if(SSL_BadCertHook(model, (SSLBadCertHandler) BadCertHandler, conn)
     != SECSuccess) {
    goto error;
  }
  if(SSL_HandshakeCallback(model, (SSLHandshakeCallback) HandshakeCallback,
                           NULL) != SECSuccess)
    goto error;

  if(!data->set.ssl.verifypeer)
    /* skip the verifying of the peer */
    ;
  else if(data->set.ssl.CAfile) {
    int rc = nss_load_cert(data->set.ssl.CAfile, PR_TRUE);
    if(!rc) {
      curlerr = CURLE_SSL_CACERT_BADFILE;
      goto error;
    }
  }
  else if(data->set.ssl.CApath) {
    struct stat st;
    PRDir      *dir;
    PRDirEntry *entry;

    if(stat(data->set.ssl.CApath, &st) == -1) {
      curlerr = CURLE_SSL_CACERT_BADFILE;
      goto error;
    }

    if(S_ISDIR(st.st_mode)) {
      int rc;

      dir = PR_OpenDir(data->set.ssl.CApath);
      do {
        entry = PR_ReadDir(dir, PR_SKIP_BOTH | PR_SKIP_HIDDEN);

        if(entry) {
          char fullpath[PATH_MAX];

          snprintf(fullpath, sizeof(fullpath), "%s/%s", data->set.ssl.CApath,
                   entry->name);
          rc = nss_load_cert(fullpath, PR_TRUE);
          /* FIXME: check this return value! */
        }
      /* This is purposefully tolerant of errors so non-PEM files
       * can be in the same directory */
      } while(entry != NULL);
      PR_CloseDir(dir);
    }
  }
  infof(data,
        "  CAfile: %s\n"
        "  CApath: %s\n",
        data->set.ssl.CAfile ? data->set.ssl.CAfile : "none",
        data->set.ssl.CApath ? data->set.ssl.CApath : "none");

  if(data->set.str[STRING_CERT]) {
    char *n;
    char *nickname;

    nickname = (char *)malloc(PATH_MAX);
    if(is_file(data->set.str[STRING_CERT])) {
      n = strrchr(data->set.str[STRING_CERT], '/');
      if(n) {
        n++; /* skip last slash */
        snprintf(nickname, PATH_MAX, "PEM Token #%ld:%s", 1, n);
      }
    }
    else {
      strncpy(nickname, data->set.str[STRING_CERT], PATH_MAX);
    }
    if(nss_Init_Tokens(conn) != SECSuccess) {
      free(nickname);
      goto error;
    }
    if(!cert_stuff(conn, data->set.str[STRING_CERT],
                    data->set.str[STRING_KEY])) {
      /* failf() is already done in cert_stuff() */
      free(nickname);
      return CURLE_SSL_CERTPROBLEM;
    }

    connssl->client_nickname = strdup(nickname);
    if(SSL_GetClientAuthDataHook(model,
                                 (SSLGetClientAuthData) SelectClientCert,
                                 (void *)connssl->client_nickname) !=
       SECSuccess) {
      curlerr = CURLE_SSL_CERTPROBLEM;
      goto error;
    }

    free(nickname);

    PK11_SetPasswordFunc(nss_no_password);
  }
  else
    connssl->client_nickname = NULL;

  /* Import our model socket  onto the existing file descriptor */
  connssl->handle = PR_ImportTCPSocket(sockfd);
  connssl->handle = SSL_ImportFD(model, connssl->handle);
  if(!connssl->handle)
    goto error;
  PR_Close(model); /* We don't need this any more */

  /* Force handshake on next I/O */
  SSL_ResetHandshake(connssl->handle, /* asServer */ PR_FALSE);

  SSL_SetURL(connssl->handle, conn->host.name);

  /* Force the handshake now */
  if(SSL_ForceHandshakeWithTimeout(connssl->handle,
                                    PR_SecondsToInterval(HANDSHAKE_TIMEOUT))
      != SECSuccess) {
    if(conn->data->set.ssl.certverifyresult!=0)
      curlerr = CURLE_SSL_CACERT;
    goto error;
  }

  connssl->state = ssl_connection_complete;

  display_conn_info(conn, connssl->handle);

  return CURLE_OK;

error:
  err = PR_GetError();
  infof(data, "NSS error %d\n", err);
  if(model)
    PR_Close(model);
  return curlerr;
}