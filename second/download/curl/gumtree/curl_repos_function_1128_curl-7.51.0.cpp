static CURLcode ssh_knownhost(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

#ifdef HAVE_LIBSSH2_KNOWNHOST_API
  struct Curl_easy *data = conn->data;

  if(data->set.str[STRING_SSH_KNOWNHOSTS]) {
    /* we're asked to verify the host against a file */
    struct ssh_conn *sshc = &conn->proto.sshc;
    int rc;
    int keytype;
    size_t keylen;
    const char *remotekey = libssh2_session_hostkey(sshc->ssh_session,
                                                    &keylen, &keytype);
    int keycheck = LIBSSH2_KNOWNHOST_CHECK_FAILURE;
    int keybit = 0;

    if(remotekey) {
      /*
       * A subject to figure out is what host name we need to pass in here.
       * What host name does OpenSSH store in its file if an IDN name is
       * used?
       */
      struct libssh2_knownhost *host;
      enum curl_khmatch keymatch;
      curl_sshkeycallback func =
        data->set.ssh_keyfunc?data->set.ssh_keyfunc:sshkeycallback;
      struct curl_khkey knownkey;
      struct curl_khkey *knownkeyp = NULL;
      struct curl_khkey foundkey;

      keybit = (keytype == LIBSSH2_HOSTKEY_TYPE_RSA)?
        LIBSSH2_KNOWNHOST_KEY_SSHRSA:LIBSSH2_KNOWNHOST_KEY_SSHDSS;

#ifdef HAVE_LIBSSH2_KNOWNHOST_CHECKP
      keycheck = libssh2_knownhost_checkp(sshc->kh,
                                          conn->host.name,
                                          (conn->remote_port != PORT_SSH)?
                                          conn->remote_port:-1,
                                          remotekey, keylen,
                                          LIBSSH2_KNOWNHOST_TYPE_PLAIN|
                                          LIBSSH2_KNOWNHOST_KEYENC_RAW|
                                          keybit,
                                          &host);
#else
      keycheck = libssh2_knownhost_check(sshc->kh,
                                         conn->host.name,
                                         remotekey, keylen,
                                         LIBSSH2_KNOWNHOST_TYPE_PLAIN|
                                         LIBSSH2_KNOWNHOST_KEYENC_RAW|
                                         keybit,
                                         &host);
#endif

      infof(data, "SSH host check: %d, key: %s\n", keycheck,
            (keycheck <= LIBSSH2_KNOWNHOST_CHECK_MISMATCH)?
            host->key:"<none>");

      /* setup 'knownkey' */
      if(keycheck <= LIBSSH2_KNOWNHOST_CHECK_MISMATCH) {
        knownkey.key = host->key;
        knownkey.len = 0;
        knownkey.keytype = (keytype == LIBSSH2_HOSTKEY_TYPE_RSA)?
          CURLKHTYPE_RSA : CURLKHTYPE_DSS;
        knownkeyp = &knownkey;
      }

      /* setup 'foundkey' */
      foundkey.key = remotekey;
      foundkey.len = keylen;
      foundkey.keytype = (keytype == LIBSSH2_HOSTKEY_TYPE_RSA)?
        CURLKHTYPE_RSA : CURLKHTYPE_DSS;

      /*
       * if any of the LIBSSH2_KNOWNHOST_CHECK_* defines and the
       * curl_khmatch enum are ever modified, we need to introduce a
       * translation table here!
       */
      keymatch = (enum curl_khmatch)keycheck;

      /* Ask the callback how to behave */
      rc = func(data, knownkeyp, /* from the knownhosts file */
                &foundkey, /* from the remote host */
                keymatch, data->set.ssh_keyfunc_userp);
    }
    else
      /* no remotekey means failure! */
      rc = CURLKHSTAT_REJECT;

    switch(rc) {
    default: /* unknown return codes will equal reject */
      /* FALLTHROUGH */
    case CURLKHSTAT_REJECT:
      state(conn, SSH_SESSION_FREE);
      /* FALLTHROUGH */
    case CURLKHSTAT_DEFER:
      /* DEFER means bail out but keep the SSH_HOSTKEY state */
      result = sshc->actualcode = CURLE_PEER_FAILED_VERIFICATION;
      break;
    case CURLKHSTAT_FINE:
    case CURLKHSTAT_FINE_ADD_TO_FILE:
      /* proceed */
      if(keycheck != LIBSSH2_KNOWNHOST_CHECK_MATCH) {
        /* the found host+key didn't match but has been told to be fine
           anyway so we add it in memory */
        int addrc = libssh2_knownhost_add(sshc->kh,
                                          conn->host.name, NULL,
                                          remotekey, keylen,
                                          LIBSSH2_KNOWNHOST_TYPE_PLAIN|
                                          LIBSSH2_KNOWNHOST_KEYENC_RAW|
                                          keybit, NULL);
        if(addrc)
          infof(data, "Warning adding the known host %s failed!\n",
                conn->host.name);
        else if(rc == CURLKHSTAT_FINE_ADD_TO_FILE) {
          /* now we write the entire in-memory list of known hosts to the
             known_hosts file */
          int wrc =
            libssh2_knownhost_writefile(sshc->kh,
                                        data->set.str[STRING_SSH_KNOWNHOSTS],
                                        LIBSSH2_KNOWNHOST_FILE_OPENSSH);
          if(wrc) {
            infof(data, "Warning, writing %s failed!\n",
                  data->set.str[STRING_SSH_KNOWNHOSTS]);
          }
        }
      }
      break;
    }
  }
#else /* HAVE_LIBSSH2_KNOWNHOST_API */
  (void)conn;
#endif
  return result;
}