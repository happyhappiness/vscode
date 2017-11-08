static CURLcode ssh_statemach_act(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct SSHPROTO *sftp_scp = data->state.proto.ssh;
  struct ssh_conn *sshc = &conn->proto.sshc;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
#ifdef CURL_LIBSSH2_DEBUG
  const char *fingerprint;
#endif /* CURL_LIBSSH2_DEBUG */
  const char *host_public_key_md5;
  int rc,i;
  int err;

  switch(sshc->state) {
  case SSH_S_STARTUP:
    sshc->secondCreateDirs = 0;
    sshc->nextstate = SSH_NO_STATE;
    sshc->actualcode = CURLE_OK;

    rc = libssh2_session_startup(sshc->ssh_session, sock);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc) {
      failf(data, "Failure establishing ssh session");
      state(conn, SSH_SESSION_FREE);
      sshc->actualcode = CURLE_FAILED_INIT;
      break;
    }

    /* Set libssh2 to non-blocking, since cURL is all non-blocking */
    libssh2_session_set_blocking(sshc->ssh_session, 0);

#ifdef CURL_LIBSSH2_DEBUG
    /*
     * Before we authenticate we should check the hostkey's fingerprint
     * against our known hosts. How that is handled (reading from file,
     * whatever) is up to us. As for know not much is implemented, besides
     * showing how to get the fingerprint.
     */
    fingerprint = libssh2_hostkey_hash(sshc->ssh_session,
                                       LIBSSH2_HOSTKEY_HASH_MD5);

    /* The fingerprint points to static storage (!), don't free() it. */
    infof(data, "Fingerprint: ");
    for (rc = 0; rc < 16; rc++) {
      infof(data, "%02X ", (unsigned char) fingerprint[rc]);
    }
    infof(data, "\n");
#endif /* CURL_LIBSSH2_DEBUG */

    /* Before we authenticate we check the hostkey's MD5 fingerprint
     * against a known fingerprint, if available.  This implementation pulls
     * it from the curl option.
     */
    if(data->set.str[STRING_SSH_HOST_PUBLIC_KEY_MD5] &&
       strlen(data->set.str[STRING_SSH_HOST_PUBLIC_KEY_MD5]) == 32) {
      char buf[33];
      host_public_key_md5 = libssh2_hostkey_hash(sshc->ssh_session,
                                                 LIBSSH2_HOSTKEY_HASH_MD5);
      for (i = 0; i < 16; i++)
        snprintf(&buf[i*2], 3, "%02x",
                 (unsigned char) host_public_key_md5[i]);
      if(!strequal(buf, data->set.str[STRING_SSH_HOST_PUBLIC_KEY_MD5])) {
        failf(data,
              "Denied establishing ssh session: mismatch md5 fingerprint. "
              "Remote %s is not equal to %s",
              buf, data->set.str[STRING_SSH_HOST_PUBLIC_KEY_MD5]);
        state(conn, SSH_SESSION_FREE);
        sshc->actualcode = CURLE_PEER_FAILED_VERIFICATION;
        break;
      }
    }

    state(conn, SSH_AUTHLIST);
    break;

  case SSH_AUTHLIST:
    /* TBD - methods to check the host keys need to be done */

    /*
     * Figure out authentication methods
     * NB: As soon as we have provided a username to an openssh server we
     * must never change it later. Thus, always specify the correct username
     * here, even though the libssh2 docs kind of indicate that it should be
     * possible to get a 'generic' list (not user-specific) of authentication
     * methods, presumably with a blank username. That won't work in my
     * experience.
     * So always specify it here.
     */
    sshc->authlist = libssh2_userauth_list(sshc->ssh_session,
                                           conn->user,
                                           strlen(conn->user));

    if(!sshc->authlist) {
      if((err = libssh2_session_last_errno(sshc->ssh_session)) ==
         LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else {
        state(conn, SSH_SESSION_FREE);
        sshc->actualcode = libssh2_session_error_to_CURLE(err);
        break;
      }
    }
    infof(data, "SSH authentication methods available: %s\n", sshc->authlist);

    state(conn, SSH_AUTH_PKEY_INIT);
    break;

  case SSH_AUTH_PKEY_INIT:
    /*
     * Check the supported auth types in the order I feel is most secure
     * with the requested type of authentication
     */
    sshc->authed = FALSE;

    if((data->set.ssh_auth_types & CURLSSH_AUTH_PUBLICKEY) &&
       (strstr(sshc->authlist, "publickey") != NULL)) {
      char *home;

      sshc->rsa_pub = sshc->rsa = NULL;

      /* To ponder about: should really the lib be messing about with the
         HOME environment variable etc? */
      home = curl_getenv("HOME");

      if(data->set.str[STRING_SSH_PUBLIC_KEY])
        sshc->rsa_pub = aprintf("%s", data->set.str[STRING_SSH_PUBLIC_KEY]);
      else if(home)
        sshc->rsa_pub = aprintf("%s/.ssh/id_dsa.pub", home);
      else
        /* as a final resort, try current dir! */
        sshc->rsa_pub = strdup("id_dsa.pub");

      if(sshc->rsa_pub == NULL) {
        Curl_safefree(home);
        home = NULL;
        state(conn, SSH_SESSION_FREE);
        sshc->actualcode = CURLE_OUT_OF_MEMORY;
        break;
      }

      if(data->set.str[STRING_SSH_PRIVATE_KEY])
        sshc->rsa = aprintf("%s", data->set.str[STRING_SSH_PRIVATE_KEY]);
      else if(home)
        sshc->rsa = aprintf("%s/.ssh/id_dsa", home);
      else
        /* as a final resort, try current dir! */
        sshc->rsa = strdup("id_dsa");

      if(sshc->rsa == NULL) {
        Curl_safefree(home);
        home = NULL;
        Curl_safefree(sshc->rsa_pub);
        sshc->rsa_pub = NULL;
        state(conn, SSH_SESSION_FREE);
        sshc->actualcode = CURLE_OUT_OF_MEMORY;
        break;
      }

      sshc->passphrase = data->set.str[STRING_KEY_PASSWD];
      if(!sshc->passphrase)
        sshc->passphrase = "";

      Curl_safefree(home);
      home = NULL;

      infof(data, "Using ssh public key file %s\n", sshc->rsa_pub);
      infof(data, "Using ssh private key file %s\n", sshc->rsa);

      state(conn, SSH_AUTH_PKEY);
    }
    else {
      state(conn, SSH_AUTH_PASS_INIT);
    }
    break;

  case SSH_AUTH_PKEY:
    /* The function below checks if the files exists, no need to stat() here.
     */
    rc = libssh2_userauth_publickey_fromfile(sshc->ssh_session,
                                             conn->user, sshc->rsa_pub,
                                             sshc->rsa, sshc->passphrase);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }

    Curl_safefree(sshc->rsa_pub);
    sshc->rsa_pub = NULL;
    Curl_safefree(sshc->rsa);
    sshc->rsa = NULL;

    if(rc == 0) {
      sshc->authed = TRUE;
      infof(data, "Initialized SSH public key authentication\n");
      state(conn, SSH_AUTH_DONE);
    }
    else {
      char *err_msg;
      (void)libssh2_session_last_error(sshc->ssh_session,
                                       &err_msg, NULL, 0);
      infof(data, "SSH public key authentication failed: %s\n", err_msg);
      state(conn, SSH_AUTH_PASS_INIT);
    }
    break;

  case SSH_AUTH_PASS_INIT:
    if((data->set.ssh_auth_types & CURLSSH_AUTH_PASSWORD) &&
       (strstr(sshc->authlist, "password") != NULL)) {
      state(conn, SSH_AUTH_PASS);
    }
    else {
      state(conn, SSH_AUTH_HOST_INIT);
    }
    break;

  case SSH_AUTH_PASS:
    rc = libssh2_userauth_password(sshc->ssh_session, conn->user,
                                   conn->passwd);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc == 0) {
      sshc->authed = TRUE;
      infof(data, "Initialized password authentication\n");
      state(conn, SSH_AUTH_DONE);
    }
    else {
      state(conn, SSH_AUTH_HOST_INIT);
    }
    break;

  case SSH_AUTH_HOST_INIT:
    if((data->set.ssh_auth_types & CURLSSH_AUTH_HOST) &&
       (strstr(sshc->authlist, "hostbased") != NULL)) {
      state(conn, SSH_AUTH_HOST);
    }
    else {
      state(conn, SSH_AUTH_KEY_INIT);
    }
    break;

  case SSH_AUTH_HOST:
    state(conn, SSH_AUTH_KEY_INIT);
    break;

  case SSH_AUTH_KEY_INIT:
    if((data->set.ssh_auth_types & CURLSSH_AUTH_KEYBOARD)
       && (strstr(sshc->authlist, "keyboard-interactive") != NULL)) {
      state(conn, SSH_AUTH_KEY);
    }
    else {
      state(conn, SSH_AUTH_DONE);
    }
    break;

  case SSH_AUTH_KEY:
    /* Authentication failed. Continue with keyboard-interactive now. */
    rc = libssh2_userauth_keyboard_interactive_ex(sshc->ssh_session,
                                                  conn->user,
                                                  strlen(conn->user),
                                                  &kbd_callback);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc == 0) {
      sshc->authed = TRUE;
      infof(data, "Initialized keyboard interactive authentication\n");
    }
    state(conn, SSH_AUTH_DONE);
    break;

  case SSH_AUTH_DONE:
    if(!sshc->authed) {
      failf(data, "Authentication failure");
      state(conn, SSH_SESSION_FREE);
      sshc->actualcode = CURLE_LOGIN_DENIED;
      break;
    }

    /*
     * At this point we have an authenticated ssh session.
     */
    infof(data, "Authentication complete\n");

    conn->sockfd = sock;
    conn->writesockfd = CURL_SOCKET_BAD;

    if(conn->protocol == PROT_SFTP) {
      state(conn, SSH_SFTP_INIT);
      break;
    }
    infof(data, "SSH CONNECT phase done\n");
    state(conn, SSH_STOP);
    break;

  case SSH_SFTP_INIT:
    /*
     * Start the libssh2 sftp session
     */
    sshc->sftp_session = libssh2_sftp_init(sshc->ssh_session);
    if(!sshc->sftp_session) {
      if(libssh2_session_last_errno(sshc->ssh_session) ==
         LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else {
        char *err_msg;

        (void)libssh2_session_last_error(sshc->ssh_session,
                                         &err_msg, NULL, 0);
        failf(data, "Failure initializing sftp session: %s", err_msg);
        state(conn, SSH_SESSION_FREE);
        sshc->actualcode = CURLE_FAILED_INIT;
        break;
      }
    }
    state(conn, SSH_SFTP_REALPATH);
    break;

  case SSH_SFTP_REALPATH:
  {
    char tempHome[PATH_MAX];

    /*
     * Get the "home" directory
     */
    rc = libssh2_sftp_realpath(sshc->sftp_session, ".",
                               tempHome, PATH_MAX-1);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc > 0) {
      /* It seems that this string is not always NULL terminated */
      tempHome[rc] = '\0';
      sshc->homedir = (char *)strdup(tempHome);
      if(!sshc->homedir) {
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = CURLE_OUT_OF_MEMORY;
        break;
      }
    }
    else {
      /* Return the error type */
      err = libssh2_sftp_last_error(sshc->sftp_session);
      result = sftp_libssh2_error_to_CURLE(err);
      DEBUGF(infof(data, "error = %d makes libcurl = %d\n", err, result));
      state(conn, SSH_STOP);
      break;
    }
  }
  /* This is the last step in the SFTP connect phase. Do note that while
     we get the homedir here, we get the "workingpath" in the DO action
     since the homedir will remain the same between request but the
     working path will not. */
  DEBUGF(infof(data, "SSH CONNECT phase done\n"));
  state(conn, SSH_STOP);
  break;

  case SSH_SFTP_QUOTE_INIT:

    result = ssh_getworkingpath(conn, sshc->homedir, &sftp_scp->path);
    if(result) {
      sshc->actualcode = result;
      state(conn, SSH_STOP);
      break;
    }

    if(data->set.quote) {
      infof(data, "Sending quote commands\n");
      sshc->quote_item = data->set.quote;
      state(conn, SSH_SFTP_QUOTE);
    }
    else {
      state(conn, SSH_SFTP_TRANS_INIT);
    }
    break;

  case SSH_SFTP_POSTQUOTE_INIT:
    if(data->set.postquote) {
      infof(data, "Sending quote commands\n");
      sshc->quote_item = data->set.postquote;
      state(conn, SSH_SFTP_QUOTE);
    }
    else {
      state(conn, SSH_STOP);
    }
    break;

  case SSH_SFTP_QUOTE:
    /* Send any quote commands */
  {
    const char *cp;

    /*
     * Support some of the "FTP" commands
     */
    if(curl_strnequal(sshc->quote_item->data, "PWD", 3)) {
      /* output debug output if that is requested */
      if(data->set.verbose) {
        char tmp[PATH_MAX+1];

        Curl_debug(data, CURLINFO_HEADER_OUT, (char *)"PWD\n", 4, conn);
        snprintf(tmp, PATH_MAX, "257 \"%s\" is current directory.\n",
                 sftp_scp->path);
        Curl_debug(data, CURLINFO_HEADER_IN, tmp, strlen(tmp), conn);
      }
      state(conn, SSH_SFTP_NEXT_QUOTE);
      break;
    }
    else if(sshc->quote_item->data) {
      /*
       * the arguments following the command must be separated from the
       * command with a space so we can check for it unconditionally
       */
      cp = strchr(sshc->quote_item->data, ' ');
      if(cp == NULL) {
        failf(data, "Syntax error in SFTP command. Supply parameter(s)!");
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = CURLE_QUOTE_ERROR;
        break;
      }

      /*
       * also, every command takes at least one argument so we get that
       * first argument right now
       */
      result = get_pathname(&cp, &sshc->quote_path1);
      if(result) {
        if(result == CURLE_OUT_OF_MEMORY)
          failf(data, "Out of memory");
        else
          failf(data, "Syntax error: Bad first parameter");
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = result;
        break;
      }

      /*
       * SFTP is a binary protocol, so we don't send text commands to
       * the server. Instead, we scan for commands for commands used by
       * OpenSSH's sftp program and call the appropriate libssh2
       * functions.
       */
      if(curl_strnequal(sshc->quote_item->data, "chgrp ", 6) ||
         curl_strnequal(sshc->quote_item->data, "chmod ", 6) ||
         curl_strnequal(sshc->quote_item->data, "chown ", 6) ) {
        /* attribute change */

        /* sshc->quote_path1 contains the mode to set */
        /* get the destination */
        result = get_pathname(&cp, &sshc->quote_path2);
        if(result) {
          if(result == CURLE_OUT_OF_MEMORY)
            failf(data, "Out of memory");
          else
            failf(data, "Syntax error in chgrp/chmod/chown: "
                  "Bad second parameter");
          Curl_safefree(sshc->quote_path1);
          sshc->quote_path1 = NULL;
          state(conn, SSH_SFTP_CLOSE);
          sshc->actualcode = result;
          break;
        }
        memset(&sshc->quote_attrs, 0, sizeof(LIBSSH2_SFTP_ATTRIBUTES));
        state(conn, SSH_SFTP_QUOTE_STAT);
        break;
      }
      else if(curl_strnequal(sshc->quote_item->data, "ln ", 3) ||
              curl_strnequal(sshc->quote_item->data, "symlink ", 8)) {
        /* symbolic linking */
        /* sshc->quote_path1 is the source */
        /* get the destination */
        result = get_pathname(&cp, &sshc->quote_path2);
        if(result) {
          if(result == CURLE_OUT_OF_MEMORY)
            failf(data, "Out of memory");
          else
            failf(data,
                  "Syntax error in ln/symlink: Bad second parameter");
          Curl_safefree(sshc->quote_path1);
          sshc->quote_path1 = NULL;
          state(conn, SSH_SFTP_CLOSE);
          sshc->actualcode = result;
          break;
        }
        state(conn, SSH_SFTP_QUOTE_SYMLINK);
        break;
      }
      else if(curl_strnequal(sshc->quote_item->data, "mkdir ", 6)) {
        /* create dir */
        state(conn, SSH_SFTP_QUOTE_MKDIR);
        break;
      }
      else if(curl_strnequal(sshc->quote_item->data, "rename ", 7)) {
        /* rename file */
        /* first param is the source path */
        /* second param is the dest. path */
        result = get_pathname(&cp, &sshc->quote_path2);
        if(result) {
          if(result == CURLE_OUT_OF_MEMORY)
            failf(data, "Out of memory");
          else
            failf(data, "Syntax error in rename: Bad second parameter");
          Curl_safefree(sshc->quote_path1);
          sshc->quote_path1 = NULL;
          state(conn, SSH_SFTP_CLOSE);
          sshc->actualcode = result;
          break;
        }
        state(conn, SSH_SFTP_QUOTE_RENAME);
        break;
      }
      else if(curl_strnequal(sshc->quote_item->data, "rmdir ", 6)) {
        /* delete dir */
        state(conn, SSH_SFTP_QUOTE_RMDIR);
        break;
      }
      else if(curl_strnequal(sshc->quote_item->data, "rm ", 3)) {
        state(conn, SSH_SFTP_QUOTE_UNLINK);
        break;
      }

      failf(data, "Unknown SFTP command");
      Curl_safefree(sshc->quote_path1);
      sshc->quote_path1 = NULL;
      Curl_safefree(sshc->quote_path2);
      sshc->quote_path2 = NULL;
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_QUOTE_ERROR;
      break;
    }
  }
  if(!sshc->quote_item) {
    state(conn, SSH_SFTP_TRANS_INIT);
  }
  break;

  case SSH_SFTP_NEXT_QUOTE:
    if(sshc->quote_path1) {
      Curl_safefree(sshc->quote_path1);
      sshc->quote_path1 = NULL;
    }
    if(sshc->quote_path2) {
      Curl_safefree(sshc->quote_path2);
      sshc->quote_path2 = NULL;
    }

    sshc->quote_item = sshc->quote_item->next;

    if(sshc->quote_item) {
      state(conn, SSH_SFTP_QUOTE);
    }
    else {
      if(sshc->nextstate != SSH_NO_STATE) {
        state(conn, sshc->nextstate);
        sshc->nextstate = SSH_NO_STATE;
      }
      else {
        state(conn, SSH_SFTP_TRANS_INIT);
      }
    }
    break;

  case SSH_SFTP_QUOTE_STAT:
    rc = libssh2_sftp_stat(sshc->sftp_session, sshc->quote_path2,
                           &sshc->quote_attrs);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc != 0) { /* get those attributes */
      err = libssh2_sftp_last_error(sshc->sftp_session);
      Curl_safefree(sshc->quote_path1);
      sshc->quote_path1 = NULL;
      Curl_safefree(sshc->quote_path2);
      sshc->quote_path2 = NULL;
      failf(data, "Attempt to get SFTP stats failed: %s",
            sftp_libssh2_strerror(err));
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_QUOTE_ERROR;
      break;
    }

    /* Now set the new attributes... */
    if(curl_strnequal(sshc->quote_item->data, "chgrp", 5)) {
      sshc->quote_attrs.gid = strtol(sshc->quote_path1, NULL, 10);
      if(sshc->quote_attrs.gid == 0 && !ISDIGIT(sshc->quote_path1[0])) {
        Curl_safefree(sshc->quote_path1);
        sshc->quote_path1 = NULL;
        Curl_safefree(sshc->quote_path2);
        sshc->quote_path2 = NULL;
        failf(data, "Syntax error: chgrp gid not a number");
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = CURLE_QUOTE_ERROR;
        break;
      }
    }
    else if(curl_strnequal(sshc->quote_item->data, "chmod", 5)) {
      sshc->quote_attrs.permissions = strtol(sshc->quote_path1, NULL, 8);
      /* permissions are octal */
      if(sshc->quote_attrs.permissions == 0 &&
         !ISDIGIT(sshc->quote_path1[0])) {
        Curl_safefree(sshc->quote_path1);
        sshc->quote_path1 = NULL;
        Curl_safefree(sshc->quote_path2);
        sshc->quote_path2 = NULL;
        failf(data, "Syntax error: chmod permissions not a number");
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = CURLE_QUOTE_ERROR;
        break;
      }
    }
    else if(curl_strnequal(sshc->quote_item->data, "chown", 5)) {
      sshc->quote_attrs.uid = strtol(sshc->quote_path1, NULL, 10);
      if(sshc->quote_attrs.uid == 0 && !ISDIGIT(sshc->quote_path1[0])) {
        Curl_safefree(sshc->quote_path1);
        sshc->quote_path1 = NULL;
        Curl_safefree(sshc->quote_path2);
        sshc->quote_path2 = NULL;
        failf(data, "Syntax error: chown uid not a number");
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = CURLE_QUOTE_ERROR;
        break;
      }
    }

    /* Now send the completed structure... */
    state(conn, SSH_SFTP_QUOTE_SETSTAT);
    break;

  case SSH_SFTP_QUOTE_SETSTAT:
    rc = libssh2_sftp_setstat(sshc->sftp_session, sshc->quote_path2,
                              &sshc->quote_attrs);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc != 0) {
      err = libssh2_sftp_last_error(sshc->sftp_session);
      Curl_safefree(sshc->quote_path1);
      sshc->quote_path1 = NULL;
      Curl_safefree(sshc->quote_path2);
      sshc->quote_path2 = NULL;
      failf(data, "Attempt to set SFTP stats failed: %s",
            sftp_libssh2_strerror(err));
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_QUOTE_ERROR;
      break;
    }
    state(conn, SSH_SFTP_NEXT_QUOTE);
    break;

  case SSH_SFTP_QUOTE_SYMLINK:
    rc = libssh2_sftp_symlink(sshc->sftp_session, sshc->quote_path1,
                              sshc->quote_path2);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc != 0) {
      err = libssh2_sftp_last_error(sshc->sftp_session);
      Curl_safefree(sshc->quote_path1);
      sshc->quote_path1 = NULL;
      Curl_safefree(sshc->quote_path2);
      sshc->quote_path2 = NULL;
      failf(data, "symlink command failed: %s",
            sftp_libssh2_strerror(err));
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_QUOTE_ERROR;
      break;
    }
    state(conn, SSH_SFTP_NEXT_QUOTE);
    break;

  case SSH_SFTP_QUOTE_MKDIR:
    rc = libssh2_sftp_mkdir(sshc->sftp_session, sshc->quote_path1, 0755);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc != 0) {
      err = libssh2_sftp_last_error(sshc->sftp_session);
      Curl_safefree(sshc->quote_path1);
      sshc->quote_path1 = NULL;
      failf(data, "mkdir command failed: %s", sftp_libssh2_strerror(err));
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_QUOTE_ERROR;
      break;
    }
    state(conn, SSH_SFTP_NEXT_QUOTE);
    break;

  case SSH_SFTP_QUOTE_RENAME:
    rc = libssh2_sftp_rename(sshc->sftp_session, sshc->quote_path1,
                             sshc->quote_path2);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc != 0) {
      err = libssh2_sftp_last_error(sshc->sftp_session);
      Curl_safefree(sshc->quote_path1);
      sshc->quote_path1 = NULL;
      Curl_safefree(sshc->quote_path2);
      sshc->quote_path2 = NULL;
      failf(data, "rename command failed: %s", sftp_libssh2_strerror(err));
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_QUOTE_ERROR;
      break;
    }
    state(conn, SSH_SFTP_NEXT_QUOTE);
    break;

  case SSH_SFTP_QUOTE_RMDIR:
    rc = libssh2_sftp_rmdir(sshc->sftp_session, sshc->quote_path1);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc != 0) {
      err = libssh2_sftp_last_error(sshc->sftp_session);
      Curl_safefree(sshc->quote_path1);
      sshc->quote_path1 = NULL;
      failf(data, "rmdir command failed: %s", sftp_libssh2_strerror(err));
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_QUOTE_ERROR;
      break;
    }
    state(conn, SSH_SFTP_NEXT_QUOTE);
    break;

  case SSH_SFTP_QUOTE_UNLINK:
    rc = libssh2_sftp_unlink(sshc->sftp_session, sshc->quote_path1);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc != 0) {
      err = libssh2_sftp_last_error(sshc->sftp_session);
      Curl_safefree(sshc->quote_path1);
      sshc->quote_path1 = NULL;
      failf(data, "rm command failed: %s", sftp_libssh2_strerror(err));
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_QUOTE_ERROR;
      break;
    }
    state(conn, SSH_SFTP_NEXT_QUOTE);
    break;

  case SSH_SFTP_TRANS_INIT:
    if(data->set.upload)
      state(conn, SSH_SFTP_UPLOAD_INIT);
    else {
      if(sftp_scp->path[strlen(sftp_scp->path)-1] == '/')
        state(conn, SSH_SFTP_READDIR_INIT);
      else
        state(conn, SSH_SFTP_DOWNLOAD_INIT);
    }
    break;

  case SSH_SFTP_UPLOAD_INIT:
    /*
     * NOTE!!!  libssh2 requires that the destination path is a full path
     *          that includes the destination file and name OR ends in a "/"
     *          If this is not done the destination file will be named the
     *          same name as the last directory in the path.
     */

    if(data->state.resume_from != 0) {
      LIBSSH2_SFTP_ATTRIBUTES attrs;
      if(data->state.resume_from< 0) {
        rc = libssh2_sftp_stat(sshc->sftp_session, sftp_scp->path, &attrs);
        if(rc == LIBSSH2_ERROR_EAGAIN) {
          break;
        }
        else if(rc) {
          data->state.resume_from = 0;
        }
        else {
          data->state.resume_from = attrs.filesize;
        }
      }
    }

    sshc->sftp_handle =
      libssh2_sftp_open(sshc->sftp_session, sftp_scp->path,
                        /* If we have restart position then open for append */
                        (data->state.resume_from > 0)?
                        LIBSSH2_FXF_WRITE|LIBSSH2_FXF_APPEND:
                        LIBSSH2_FXF_WRITE|LIBSSH2_FXF_CREAT|LIBSSH2_FXF_TRUNC,
                        data->set.new_file_perms);

    if(!sshc->sftp_handle) {
      if(libssh2_session_last_errno(sshc->ssh_session) ==
         LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else {
        err = libssh2_sftp_last_error(sshc->sftp_session);
        if(sshc->secondCreateDirs) {
          state(conn, SSH_SFTP_CLOSE);
          sshc->actualcode = sftp_libssh2_error_to_CURLE(err);
          failf(data, "Creating the dir/file failed: %s",
                sftp_libssh2_strerror(err));
          break;
        }
        else if(((err == LIBSSH2_FX_NO_SUCH_FILE) ||
                 (err == LIBSSH2_FX_FAILURE) ||
                 (err == LIBSSH2_FX_NO_SUCH_PATH)) &&
                (data->set.ftp_create_missing_dirs &&
                 (strlen(sftp_scp->path) > 1))) {
          /* try to create the path remotely */
          sshc->secondCreateDirs = 1;
          state(conn, SSH_SFTP_CREATE_DIRS_INIT);
          break;
        }
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = sftp_libssh2_error_to_CURLE(err);
        failf(data, "Upload failed: %s", sftp_libssh2_strerror(err));
        break;
      }
    }

    /* If we have restart point then we need to seek to the correct position. */
    if(data->state.resume_from > 0) {
      /* Let's read off the proper amount of bytes from the input. */
      if(conn->seek_func) {
        curl_off_t readthisamountnow = data->state.resume_from;

        if(conn->seek_func(conn->seek_client,
                           readthisamountnow, SEEK_SET) != 0) {
          failf(data, "Could not seek stream");
          return CURLE_FTP_COULDNT_USE_REST;
        }
      }
      else {
        curl_off_t passed=0;
        curl_off_t readthisamountnow;
        curl_off_t actuallyread;
        do {
          readthisamountnow = (data->state.resume_from - passed);

          if(readthisamountnow > BUFSIZE)
            readthisamountnow = BUFSIZE;

          actuallyread =
            (curl_off_t) conn->fread_func(data->state.buffer, 1,
                                          (size_t)readthisamountnow,
                                          conn->fread_in);

          passed += actuallyread;
          if((actuallyread <= 0) || (actuallyread > readthisamountnow)) {
            /* this checks for greater-than only to make sure that the
               CURL_READFUNC_ABORT return code still aborts */
             failf(data, "Failed to read data");
            return CURLE_FTP_COULDNT_USE_REST;
          }
        } while(passed < data->state.resume_from);
      }

      /* now, decrease the size of the read */
      if(data->set.infilesize>0) {
        data->set.infilesize -= data->state.resume_from;
        data->req.size = data->set.infilesize;
        Curl_pgrsSetUploadSize(data, data->set.infilesize);
      }

      libssh2_sftp_seek(sshc->sftp_handle, data->state.resume_from);
    }
    if(data->set.infilesize>0) {
      data->req.size = data->set.infilesize;
      Curl_pgrsSetUploadSize(data, data->set.infilesize);
    }
    /* upload data */
    result = Curl_setup_transfer(conn, -1, -1, FALSE, NULL,
                                 FIRSTSOCKET, NULL);

    if(result) {
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = result;
    }
    else {
      state(conn, SSH_STOP);
    }
    break;

  case SSH_SFTP_CREATE_DIRS_INIT:
    if(strlen(sftp_scp->path) > 1) {
      sshc->slash_pos = sftp_scp->path + 1; /* ignore the leading '/' */
      state(conn, SSH_SFTP_CREATE_DIRS);
    }
    else {
      state(conn, SSH_SFTP_UPLOAD_INIT);
    }
    break;

  case SSH_SFTP_CREATE_DIRS:
    if((sshc->slash_pos = strchr(sshc->slash_pos, '/')) != NULL) {
      *sshc->slash_pos = 0;

      infof(data, "Creating directory '%s'\n", sftp_scp->path);
      state(conn, SSH_SFTP_CREATE_DIRS_MKDIR);
      break;
    }
    else {
      state(conn, SSH_SFTP_UPLOAD_INIT);
    }
    break;

  case SSH_SFTP_CREATE_DIRS_MKDIR:
    /* 'mode' - parameter is preliminary - default to 0644 */
    rc = libssh2_sftp_mkdir(sshc->sftp_session, sftp_scp->path,
                            data->set.new_directory_perms);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    *sshc->slash_pos = '/';
    ++sshc->slash_pos;
    if(rc == -1) {
      unsigned int sftp_err = 0;
      /*
       * abort if failure wasn't that the dir already exists or the
       * permission was denied (creation might succeed further
       * down the path) - retry on unspecific FAILURE also
       */
      sftp_err = libssh2_sftp_last_error(sshc->sftp_session);
      if((sftp_err != LIBSSH2_FX_FILE_ALREADY_EXISTS) &&
         (sftp_err != LIBSSH2_FX_FAILURE) &&
         (sftp_err != LIBSSH2_FX_PERMISSION_DENIED)) {
        result = sftp_libssh2_error_to_CURLE(sftp_err);
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = result;
        break;
      }
    }
    state(conn, SSH_SFTP_CREATE_DIRS);
    break;

  case SSH_SFTP_READDIR_INIT:
    /*
     * This is a directory that we are trying to get, so produce a
     * directory listing
     */
    sshc->sftp_handle = libssh2_sftp_opendir(sshc->sftp_session,
                                             sftp_scp->path);
    if(!sshc->sftp_handle) {
      if(libssh2_session_last_errno(sshc->ssh_session) ==
         LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else {
        err = libssh2_sftp_last_error(sshc->sftp_session);
        failf(data, "Could not open directory for reading: %s",
              sftp_libssh2_strerror(err));
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = sftp_libssh2_error_to_CURLE(err);
        break;
      }
    }
    if((sshc->readdir_filename = (char *)malloc(PATH_MAX+1)) == NULL) {
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_OUT_OF_MEMORY;
      break;
    }
    if((sshc->readdir_longentry = (char *)malloc(PATH_MAX+1)) == NULL) {
      Curl_safefree(sshc->readdir_filename);
      sshc->readdir_filename = NULL;
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_OUT_OF_MEMORY;
      break;
    }
    state(conn, SSH_SFTP_READDIR);
    break;

  case SSH_SFTP_READDIR:
    sshc->readdir_len = libssh2_sftp_readdir_ex(sshc->sftp_handle,
                                                sshc->readdir_filename,
                                                PATH_MAX,
                                                sshc->readdir_longentry,
                                                PATH_MAX,
                                                &sshc->readdir_attrs);
    if(sshc->readdir_len == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    if(sshc->readdir_len > 0) {
      sshc->readdir_filename[sshc->readdir_len] = '\0';

      if(data->set.ftp_list_only) {
        char *tmpLine;

        tmpLine = aprintf("%s\n", sshc->readdir_filename);
        if(tmpLine == NULL) {
          state(conn, SSH_SFTP_CLOSE);
          sshc->actualcode = CURLE_OUT_OF_MEMORY;
          break;
        }
        result = Curl_client_write(conn, CLIENTWRITE_BODY,
                                   tmpLine, sshc->readdir_len+1);
        Curl_safefree(tmpLine);

        if(result) {
          state(conn, SSH_STOP);
          break;
        }
        /* since this counts what we send to the client, we include the newline
           in this counter */
        data->req.bytecount += sshc->readdir_len+1;

        /* output debug output if that is requested */
        if(data->set.verbose) {
          Curl_debug(data, CURLINFO_DATA_OUT, sshc->readdir_filename,
                     sshc->readdir_len, conn);
        }
      }
      else {
        sshc->readdir_currLen = strlen(sshc->readdir_longentry);
        sshc->readdir_totalLen = 80 + sshc->readdir_currLen;
        sshc->readdir_line = (char *)calloc(sshc->readdir_totalLen, 1);
        if(!sshc->readdir_line) {
          Curl_safefree(sshc->readdir_filename);
          sshc->readdir_filename = NULL;
          Curl_safefree(sshc->readdir_longentry);
          sshc->readdir_longentry = NULL;
          state(conn, SSH_SFTP_CLOSE);
          sshc->actualcode = CURLE_OUT_OF_MEMORY;
          break;
        }

        memcpy(sshc->readdir_line, sshc->readdir_longentry,
               sshc->readdir_currLen);
        if((sshc->readdir_attrs.flags & LIBSSH2_SFTP_ATTR_PERMISSIONS) &&
           ((sshc->readdir_attrs.permissions & LIBSSH2_SFTP_S_IFMT) ==
            LIBSSH2_SFTP_S_IFLNK)) {
          sshc->readdir_linkPath = (char *)malloc(PATH_MAX + 1);
          if(sshc->readdir_linkPath == NULL) {
            Curl_safefree(sshc->readdir_filename);
            sshc->readdir_filename = NULL;
            Curl_safefree(sshc->readdir_longentry);
            sshc->readdir_longentry = NULL;
            state(conn, SSH_SFTP_CLOSE);
            sshc->actualcode = CURLE_OUT_OF_MEMORY;
            break;
          }

          snprintf(sshc->readdir_linkPath, PATH_MAX, "%s%s", sftp_scp->path,
                   sshc->readdir_filename);
          state(conn, SSH_SFTP_READDIR_LINK);
          break;
        }
        state(conn, SSH_SFTP_READDIR_BOTTOM);
        break;
      }
    }
    else if(sshc->readdir_len == 0) {
      Curl_safefree(sshc->readdir_filename);
      sshc->readdir_filename = NULL;
      Curl_safefree(sshc->readdir_longentry);
      sshc->readdir_longentry = NULL;
      state(conn, SSH_SFTP_READDIR_DONE);
      break;
    }
    else if(sshc->readdir_len <= 0) {
      err = libssh2_sftp_last_error(sshc->sftp_session);
      sshc->actualcode = sftp_libssh2_error_to_CURLE(err);
      failf(data, "Could not open remote file for reading: %s :: %d",
            sftp_libssh2_strerror(err),
            libssh2_session_last_errno(sshc->ssh_session));
      Curl_safefree(sshc->readdir_filename);
      sshc->readdir_filename = NULL;
      Curl_safefree(sshc->readdir_longentry);
      sshc->readdir_longentry = NULL;
      state(conn, SSH_SFTP_CLOSE);
      break;
    }
    break;

  case SSH_SFTP_READDIR_LINK:
    sshc->readdir_len = libssh2_sftp_readlink(sshc->sftp_session,
                                              sshc->readdir_linkPath,
                                              sshc->readdir_filename,
                                              PATH_MAX);
    if(sshc->readdir_len == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    Curl_safefree(sshc->readdir_linkPath);
    sshc->readdir_linkPath = NULL;
    sshc->readdir_line = realloc(sshc->readdir_line,
                                 sshc->readdir_totalLen + 4 +
                                 sshc->readdir_len);
    if(!sshc->readdir_line) {
      Curl_safefree(sshc->readdir_filename);
      sshc->readdir_filename = NULL;
      Curl_safefree(sshc->readdir_longentry);
      sshc->readdir_longentry = NULL;
      state(conn, SSH_SFTP_CLOSE);
      sshc->actualcode = CURLE_OUT_OF_MEMORY;
      break;
    }

    sshc->readdir_currLen += snprintf(sshc->readdir_line +
                                      sshc->readdir_currLen,
                                      sshc->readdir_totalLen -
                                      sshc->readdir_currLen,
                                      " -> %s",
                                      sshc->readdir_filename);

    state(conn, SSH_SFTP_READDIR_BOTTOM);
    break;

  case SSH_SFTP_READDIR_BOTTOM:
    sshc->readdir_currLen += snprintf(sshc->readdir_line +
                                      sshc->readdir_currLen,
                                      sshc->readdir_totalLen -
                                      sshc->readdir_currLen, "\n");
    result = Curl_client_write(conn, CLIENTWRITE_BODY,
                               sshc->readdir_line,
                               sshc->readdir_currLen);

    if(result == CURLE_OK) {

      /* output debug output if that is requested */
      if(data->set.verbose) {
        Curl_debug(data, CURLINFO_DATA_OUT, sshc->readdir_line,
                   sshc->readdir_currLen, conn);
      }
      data->req.bytecount += sshc->readdir_currLen;
    }
    Curl_safefree(sshc->readdir_line);
    sshc->readdir_line = NULL;
    if(result) {
      state(conn, SSH_STOP);
    }
    else
      state(conn, SSH_SFTP_READDIR);
    break;

  case SSH_SFTP_READDIR_DONE:
    if(libssh2_sftp_closedir(sshc->sftp_handle) ==
       LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    sshc->sftp_handle = NULL;
    Curl_safefree(sshc->readdir_filename);
    sshc->readdir_filename = NULL;
    Curl_safefree(sshc->readdir_longentry);
    sshc->readdir_longentry = NULL;

    /* no data to transfer */
    result = Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
    state(conn, SSH_STOP);
    break;

  case SSH_SFTP_DOWNLOAD_INIT:
    /*
     * Work on getting the specified file
     */
    sshc->sftp_handle =
      libssh2_sftp_open(sshc->sftp_session, sftp_scp->path,
                        LIBSSH2_FXF_READ, data->set.new_file_perms);
    if(!sshc->sftp_handle) {
      if(libssh2_session_last_errno(sshc->ssh_session) ==
         LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else {
        err = libssh2_sftp_last_error(sshc->sftp_session);
        failf(data, "Could not open remote file for reading: %s",
              sftp_libssh2_strerror(err));
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = sftp_libssh2_error_to_CURLE(err);
        break;
      }
    }
    state(conn, SSH_SFTP_DOWNLOAD_STAT);
    break;

  case SSH_SFTP_DOWNLOAD_STAT:
  {
    LIBSSH2_SFTP_ATTRIBUTES attrs;

    rc = libssh2_sftp_stat(sshc->sftp_session, sftp_scp->path, &attrs);
    if(rc == LIBSSH2_ERROR_EAGAIN) {
      break;
    }
    else if(rc) {
      /*
       * libssh2_sftp_open() didn't return an error, so maybe the server
       * just doesn't support stat()
       */
      data->req.size = -1;
      data->req.maxdownload = -1;
    }
    else {
      data->req.size = attrs.filesize;
      data->req.maxdownload = attrs.filesize;
      Curl_pgrsSetDownloadSize(data, attrs.filesize);
    }

    /* We can resume if we can seek to the resume position */
    if(data->state.resume_from) {
      if(data->state.resume_from< 0) {
        /* We're supposed to download the last abs(from) bytes */
        if((curl_off_t)attrs.filesize < -data->state.resume_from) {
          failf(data, "Offset (%"
                FORMAT_OFF_T ") was beyond file size (%" FORMAT_OFF_T ")",
                data->state.resume_from, attrs.filesize);
          return CURLE_BAD_DOWNLOAD_RESUME;
        }
        /* download from where? */
        data->state.resume_from = attrs.filesize - data->state.resume_from;
      }
      else {
        if((curl_off_t)attrs.filesize < data->state.resume_from) {
          failf(data, "Offset (%" FORMAT_OFF_T
                ") was beyond file size (%" FORMAT_OFF_T ")",
                data->state.resume_from, attrs.filesize);
          return CURLE_BAD_DOWNLOAD_RESUME;
        }
      }
      /* Does a completed file need to be seeked and started or closed ? */
      /* Now store the number of bytes we are expected to download */
      data->req.size = attrs.filesize - data->state.resume_from;
      data->req.maxdownload = attrs.filesize - data->state.resume_from;
      Curl_pgrsSetDownloadSize(data,
                               attrs.filesize - data->state.resume_from);
      libssh2_sftp_seek(sshc->sftp_handle, data->state.resume_from);
    }
  }
  /* Setup the actual download */
  if(data->req.size == 0) {
    /* no data to transfer */
    result = Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
    infof(data, "File already completely downloaded\n");
    state(conn, SSH_STOP);
    break;
  }
  else {
    result = Curl_setup_transfer(conn, FIRSTSOCKET, data->req.size,
                                 FALSE, NULL, -1, NULL);
  }
  if(result) {
    state(conn, SSH_SFTP_CLOSE);
    sshc->actualcode = result;
  }
  else {
    state(conn, SSH_STOP);
  }
  break;

  case SSH_SFTP_CLOSE:
    if(sshc->sftp_handle) {
      rc = libssh2_sftp_close(sshc->sftp_handle);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc < 0) {
        infof(data, "Failed to close libssh2 file\n");
      }
      sshc->sftp_handle = NULL;
    }
    Curl_safefree(sftp_scp->path);
    sftp_scp->path = NULL;

    DEBUGF(infof(data, "SFTP DONE done\n"));
#if 0 /* PREV */
    state(conn, SSH_SFTP_SHUTDOWN);
#endif
    state(conn, SSH_STOP);
    result = sshc->actualcode;
    break;

  case SSH_SFTP_SHUTDOWN:
    if(sshc->sftp_session) {
      rc = libssh2_sftp_shutdown(sshc->sftp_session);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc < 0) {
        infof(data, "Failed to stop libssh2 sftp subsystem\n");
      }
      sshc->sftp_session = NULL;
    }

    Curl_safefree(sshc->homedir);
    sshc->homedir = NULL;

    state(conn, SSH_SESSION_DISCONNECT);
    break;

  case SSH_SCP_TRANS_INIT:
    result = ssh_getworkingpath(conn, sshc->homedir, &sftp_scp->path);
    if(result) {
      sshc->actualcode = result;
      state(conn, SSH_STOP);
      break;
    }

    if(data->set.upload) {
      if(data->set.infilesize < 0) {
        failf(data, "SCP requires a known file size for upload");
        sshc->actualcode = CURLE_UPLOAD_FAILED;
        state(conn, SSH_SCP_CHANNEL_FREE);
        break;
      }
      state(conn, SSH_SCP_UPLOAD_INIT);
    }
    else {
      state(conn, SSH_SCP_DOWNLOAD_INIT);
    }
    break;

  case SSH_SCP_UPLOAD_INIT:
    /*
     * libssh2 requires that the destination path is a full path that
     * includes the destination file and name OR ends in a "/" .  If this is
     * not done the destination file will be named the same name as the last
     * directory in the path.
     */
    sshc->ssh_channel =
      libssh2_scp_send_ex(sshc->ssh_session, sftp_scp->path,
                          data->set.new_file_perms,
                          data->set.infilesize, 0, 0);
    if(!sshc->ssh_channel) {
      if(libssh2_session_last_errno(sshc->ssh_session) ==
         LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else {
        int ssh_err;
        char *err_msg;

        ssh_err = libssh2_session_last_error(sshc->ssh_session,
                                             &err_msg, NULL, 0);
        failf(conn->data, "%s", err_msg);
        state(conn, SSH_SCP_CHANNEL_FREE);
        sshc->actualcode = libssh2_session_error_to_CURLE(ssh_err);
        break;
      }
    }

    /* upload data */
    result = Curl_setup_transfer(conn, -1, data->req.size, FALSE, NULL,
                                 FIRSTSOCKET, NULL);

    if(result) {
      state(conn, SSH_SCP_CHANNEL_FREE);
      sshc->actualcode = result;
    }
    else {
      state(conn, SSH_STOP);
    }
    break;

  case SSH_SCP_DOWNLOAD_INIT:
  {
    /*
     * We must check the remote file; if it is a directory no values will
     * be set in sb
     */
    struct stat sb;
    curl_off_t bytecount;

    /* clear the struct scp recv will fill in */
    memset(&sb, 0, sizeof(struct stat));

    /* get a fresh new channel from the ssh layer */
    sshc->ssh_channel = libssh2_scp_recv(sshc->ssh_session,
                                         sftp_scp->path, &sb);
    if(!sshc->ssh_channel) {
      if(libssh2_session_last_errno(sshc->ssh_session) ==
         LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else {
        int ssh_err;
        char *err_msg;

        ssh_err = libssh2_session_last_error(sshc->ssh_session,
                                             &err_msg, NULL, 0);
        failf(conn->data, "%s", err_msg);
        state(conn, SSH_SCP_CHANNEL_FREE);
        sshc->actualcode = libssh2_session_error_to_CURLE(ssh_err);
        break;
      }
    }

    /* download data */
    bytecount = (curl_off_t)sb.st_size;
    data->req.maxdownload =  (curl_off_t)sb.st_size;
    result = Curl_setup_transfer(conn, FIRSTSOCKET,
                                 bytecount, FALSE, NULL, -1, NULL);

    if(result) {
      state(conn, SSH_SCP_CHANNEL_FREE);
      sshc->actualcode = result;
    }
    else
      state(conn, SSH_STOP);
  }
  break;

  case SSH_SCP_DONE:
    if(data->set.upload)
      state(conn, SSH_SCP_SEND_EOF);
    else
      state(conn, SSH_SCP_CHANNEL_FREE);
    break;

  case SSH_SCP_SEND_EOF:
    if(sshc->ssh_channel) {
      rc = libssh2_channel_send_eof(sshc->ssh_channel);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc) {
        infof(data, "Failed to send libssh2 channel EOF\n");
      }
    }
    state(conn, SSH_SCP_WAIT_EOF);
    break;

  case SSH_SCP_WAIT_EOF:
    if(sshc->ssh_channel) {
      rc = libssh2_channel_wait_eof(sshc->ssh_channel);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc) {
        infof(data, "Failed to get channel EOF: %d\n", rc);
      }
    }
    state(conn, SSH_SCP_WAIT_CLOSE);
    break;

  case SSH_SCP_WAIT_CLOSE:
    if(sshc->ssh_channel) {
      rc = libssh2_channel_wait_closed(sshc->ssh_channel);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc) {
        infof(data, "Channel failed to close: %d\n", rc);
      }
    }
    state(conn, SSH_SCP_CHANNEL_FREE);
    break;

  case SSH_SCP_CHANNEL_FREE:
    if(sshc->ssh_channel) {
      rc = libssh2_channel_free(sshc->ssh_channel);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc < 0) {
        infof(data, "Failed to free libssh2 scp subsystem\n");
      }
      sshc->ssh_channel = NULL;
    }
    DEBUGF(infof(data, "SCP DONE phase complete\n"));
#if 0 /* PREV */
    state(conn, SSH_SESSION_DISCONNECT);
#endif
    state(conn, SSH_STOP);
    result = sshc->actualcode;
    break;

  case SSH_SESSION_DISCONNECT:
    if(sshc->ssh_session) {
      rc = libssh2_session_disconnect(sshc->ssh_session, "Shutdown");
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc < 0) {
        infof(data, "Failed to disconnect libssh2 session\n");
      }
    }

    Curl_safefree(sshc->homedir);
    sshc->homedir = NULL;

    state(conn, SSH_SESSION_FREE);
    break;

  case SSH_SESSION_FREE:
    if(sshc->ssh_session) {
      rc = libssh2_session_free(sshc->ssh_session);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc < 0) {
        infof(data, "Failed to free libssh2 session\n");
      }
      sshc->ssh_session = NULL;
    }
    sshc->nextstate = SSH_NO_STATE;
    state(conn, SSH_STOP);
    result = sshc->actualcode;
    break;

  case SSH_QUIT:
    /* fallthrough, just stop! */
  default:
    /* internal error */
    sshc->nextstate = SSH_NO_STATE;
    state(conn, SSH_STOP);
    break;
  }

  return result;
}