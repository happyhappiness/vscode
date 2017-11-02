static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct SSHPROTO *sftp_scp = data->req.protop;
  struct ssh_conn *sshc = &conn->proto.sshc;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  char *new_readdir_line;
  int rc = LIBSSH2_ERROR_NONE;
  int err;
  int seekerr = CURL_SEEKFUNC_OK;
  *block = 0; /* we're not blocking by default */

  do {

    switch(sshc->state) {
    case SSH_INIT:
      sshc->secondCreateDirs = 0;
      sshc->nextstate = SSH_NO_STATE;
      sshc->actualcode = CURLE_OK;

      /* Set libssh2 to non-blocking, since everything internally is
         non-blocking */
      libssh2_session_set_blocking(sshc->ssh_session, 0);

      state(conn, SSH_S_STARTUP);
      /* fall-through */

    case SSH_S_STARTUP:
      rc = libssh2_session_startup(sshc->ssh_session, (int)sock);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc) {
        failf(data, "Failure establishing ssh session");
        state(conn, SSH_SESSION_FREE);
        sshc->actualcode = CURLE_FAILED_INIT;
        break;
      }

      state(conn, SSH_HOSTKEY);

      /* fall-through */
    case SSH_HOSTKEY:
      /*
       * Before we authenticate we should check the hostkey's fingerprint
       * against our known hosts. How that is handled (reading from file,
       * whatever) is up to us.
       */
      result = ssh_check_fingerprint(conn);
      if(!result)
        state(conn, SSH_AUTHLIST);
      /* ssh_check_fingerprint sets state appropriately on error */
      break;

    case SSH_AUTHLIST:
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
                                             curlx_uztoui(strlen(conn->user)));

      if(!sshc->authlist) {
        if(libssh2_userauth_authenticated(sshc->ssh_session)) {
          sshc->authed = TRUE;
          infof(data, "SSH user accepted with no authentication\n");
          state(conn, SSH_AUTH_DONE);
          break;
        }
        else if((err = libssh2_session_last_errno(sshc->ssh_session)) ==
           LIBSSH2_ERROR_EAGAIN) {
          rc = LIBSSH2_ERROR_EAGAIN;
          break;
        }
        else {
          state(conn, SSH_SESSION_FREE);
          sshc->actualcode = libssh2_session_error_to_CURLE(err);
          break;
        }
      }
      infof(data, "SSH authentication methods available: %s\n",
            sshc->authlist);

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
        char *home = NULL;
        bool out_of_memory = FALSE;

        sshc->rsa_pub = sshc->rsa = NULL;

        /* To ponder about: should really the lib be messing about with the
           HOME environment variable etc? */
        home = curl_getenv("HOME");

        if(data->set.str[STRING_SSH_PRIVATE_KEY])
          sshc->rsa = strdup(data->set.str[STRING_SSH_PRIVATE_KEY]);
        else {
          /* If no private key file is specified, try some common paths. */
          if(home) {
            /* Try ~/.ssh first. */
            sshc->rsa = aprintf("%s/.ssh/id_rsa", home);
            if(!sshc->rsa)
              out_of_memory = TRUE;
            else if(access(sshc->rsa, R_OK) != 0) {
              Curl_safefree(sshc->rsa);
              sshc->rsa = aprintf("%s/.ssh/id_dsa", home);
              if(!sshc->rsa)
                out_of_memory = TRUE;
              else if(access(sshc->rsa, R_OK) != 0) {
                Curl_safefree(sshc->rsa);
              }
            }
          }
          if(!out_of_memory && !sshc->rsa) {
            /* Nothing found; try the current dir. */
            sshc->rsa = strdup("id_rsa");
            if(sshc->rsa && access(sshc->rsa, R_OK) != 0) {
              Curl_safefree(sshc->rsa);
              sshc->rsa = strdup("id_dsa");
              if(sshc->rsa && access(sshc->rsa, R_OK) != 0) {
                Curl_safefree(sshc->rsa);
                /* Out of guesses. Set to the empty string to avoid
                 * surprising info messages. */
                sshc->rsa = strdup("");
              }
            }
          }
        }

        /*
         * Unless the user explicitly specifies a public key file, let
         * libssh2 extract the public key from the private key file.
         * This is done by simply passing sshc->rsa_pub = NULL.
         */
        if(data->set.str[STRING_SSH_PUBLIC_KEY]) {
          sshc->rsa_pub = strdup(data->set.str[STRING_SSH_PUBLIC_KEY]);
          if(!sshc->rsa_pub)
            out_of_memory = TRUE;
        }

        if(out_of_memory || sshc->rsa == NULL) {
          Curl_safefree(home);
          Curl_safefree(sshc->rsa);
          Curl_safefree(sshc->rsa_pub);
          state(conn, SSH_SESSION_FREE);
          sshc->actualcode = CURLE_OUT_OF_MEMORY;
          break;
        }

        sshc->passphrase = data->set.str[STRING_KEY_PASSWD];
        if(!sshc->passphrase)
          sshc->passphrase = "";

        Curl_safefree(home);

        infof(data, "Using SSH public key file '%s'\n", sshc->rsa_pub);
        infof(data, "Using SSH private key file '%s'\n", sshc->rsa);

        state(conn, SSH_AUTH_PKEY);
      }
      else {
        state(conn, SSH_AUTH_PASS_INIT);
      }
      break;

    case SSH_AUTH_PKEY:
      /* The function below checks if the files exists, no need to stat() here.
       */
      rc = libssh2_userauth_publickey_fromfile_ex(sshc->ssh_session,
                                                  conn->user,
                                                  curlx_uztoui(
                                                    strlen(conn->user)),
                                                  sshc->rsa_pub,
                                                  sshc->rsa, sshc->passphrase);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }

      Curl_safefree(sshc->rsa_pub);
      Curl_safefree(sshc->rsa);

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
      rc = libssh2_userauth_password_ex(sshc->ssh_session, conn->user,
                                        curlx_uztoui(strlen(conn->user)),
                                        conn->passwd,
                                        curlx_uztoui(strlen(conn->passwd)),
                                        NULL);
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
        state(conn, SSH_AUTH_AGENT_INIT);
      }
      break;

    case SSH_AUTH_HOST:
      state(conn, SSH_AUTH_AGENT_INIT);
      break;

    case SSH_AUTH_AGENT_INIT:
#ifdef HAVE_LIBSSH2_AGENT_API
      if((data->set.ssh_auth_types & CURLSSH_AUTH_AGENT)
         && (strstr(sshc->authlist, "publickey") != NULL)) {

        /* Connect to the ssh-agent */
        /* The agent could be shared by a curl thread i believe
           but nothing obvious as keys can be added/removed at any time */
        if(!sshc->ssh_agent) {
          sshc->ssh_agent = libssh2_agent_init(sshc->ssh_session);
          if(!sshc->ssh_agent) {
            infof(data, "Could not create agent object\n");

            state(conn, SSH_AUTH_KEY_INIT);
            break;
          }
        }

        rc = libssh2_agent_connect(sshc->ssh_agent);
        if(rc == LIBSSH2_ERROR_EAGAIN)
          break;
        if(rc < 0) {
          infof(data, "Failure connecting to agent\n");
          state(conn, SSH_AUTH_KEY_INIT);
        }
        else {
          state(conn, SSH_AUTH_AGENT_LIST);
        }
      }
      else
#endif /* HAVE_LIBSSH2_AGENT_API */
        state(conn, SSH_AUTH_KEY_INIT);
      break;

    case SSH_AUTH_AGENT_LIST:
#ifdef HAVE_LIBSSH2_AGENT_API
      rc = libssh2_agent_list_identities(sshc->ssh_agent);

      if(rc == LIBSSH2_ERROR_EAGAIN)
        break;
      if(rc < 0) {
        infof(data, "Failure requesting identities to agent\n");
        state(conn, SSH_AUTH_KEY_INIT);
      }
      else {
        state(conn, SSH_AUTH_AGENT);
        sshc->sshagent_prev_identity = NULL;
      }
#endif
      break;

    case SSH_AUTH_AGENT:
#ifdef HAVE_LIBSSH2_AGENT_API
      /* as prev_identity evolves only after an identity user auth finished we
         can safely request it again as long as EAGAIN is returned here or by
         libssh2_agent_userauth */
      rc = libssh2_agent_get_identity(sshc->ssh_agent,
                                      &sshc->sshagent_identity,
                                      sshc->sshagent_prev_identity);
      if(rc == LIBSSH2_ERROR_EAGAIN)
        break;

      if(rc == 0) {
        rc = libssh2_agent_userauth(sshc->ssh_agent, conn->user,
                                    sshc->sshagent_identity);

        if(rc < 0) {
          if(rc != LIBSSH2_ERROR_EAGAIN) {
            /* tried and failed? go to next identity */
            sshc->sshagent_prev_identity = sshc->sshagent_identity;
          }
          break;
        }
      }

      if(rc < 0)
        infof(data, "Failure requesting identities to agent\n");
      else if(rc == 1)
        infof(data, "No identity would match\n");

      if(rc == LIBSSH2_ERROR_NONE) {
        sshc->authed = TRUE;
        infof(data, "Agent based authentication successful\n");
        state(conn, SSH_AUTH_DONE);
      }
      else
        state(conn, SSH_AUTH_KEY_INIT);
#endif
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
                                                    curlx_uztoui(
                                                      strlen(conn->user)),
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

      Curl_pgrsTime(conn->data, TIMER_APPCONNECT); /* SSH is connected */

      conn->sockfd = sock;
      conn->writesockfd = CURL_SOCKET_BAD;

      if(conn->handler->protocol == CURLPROTO_SFTP) {
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
          rc = LIBSSH2_ERROR_EAGAIN;
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
      rc = sftp_libssh2_realpath(sshc->sftp_session, ".",
                                 tempHome, PATH_MAX-1);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc > 0) {
        /* It seems that this string is not always NULL terminated */
        tempHome[rc] = '\0';
        sshc->homedir = strdup(tempHome);
        if(!sshc->homedir) {
          state(conn, SSH_SFTP_CLOSE);
          sshc->actualcode = CURLE_OUT_OF_MEMORY;
          break;
        }
        conn->data->state.most_recent_ftp_entrypath = sshc->homedir;
      }
      else {
        /* Return the error type */
        err = sftp_libssh2_last_error(sshc->sftp_session);
        result = sftp_libssh2_error_to_CURLE(err);
        sshc->actualcode = result?result:CURLE_SSH;
        DEBUGF(infof(data, "error = %d makes libcurl = %d\n",
                     err, (int)result));
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
      char *cmd = sshc->quote_item->data;
      sshc->acceptfail = FALSE;

      /* if a command starts with an asterisk, which a legal SFTP command never
         can, the command will be allowed to fail without it causing any
         aborts or cancels etc. It will cause libcurl to act as if the command
         is successful, whatever the server reponds. */

      if(cmd[0] == '*') {
        cmd++;
        sshc->acceptfail = TRUE;
      }

      if(curl_strequal("pwd", cmd)) {
        /* output debug output if that is requested */
        char *tmp = aprintf("257 \"%s\" is current directory.\n",
                            sftp_scp->path);
        if(!tmp) {
          result = CURLE_OUT_OF_MEMORY;
          state(conn, SSH_SFTP_CLOSE);
          sshc->nextstate = SSH_NO_STATE;
          break;
        }
        if(data->set.verbose) {
          Curl_debug(data, CURLINFO_HEADER_OUT, (char *)"PWD\n", 4, conn);
          Curl_debug(data, CURLINFO_HEADER_IN, tmp, strlen(tmp), conn);
        }
        /* this sends an FTP-like "header" to the header callback so that the
           current directory can be read very similar to how it is read when
           using ordinary FTP. */
        result = Curl_client_write(conn, CLIENTWRITE_HEADER, tmp, strlen(tmp));
        free(tmp);
        if(result) {
          state(conn, SSH_SFTP_CLOSE);
          sshc->nextstate = SSH_NO_STATE;
          sshc->actualcode = result;
        }
        else
          state(conn, SSH_SFTP_NEXT_QUOTE);
        break;
      }
      else if(cmd) {
        /*
         * the arguments following the command must be separated from the
         * command with a space so we can check for it unconditionally
         */
        cp = strchr(cmd, ' ');
        if(cp == NULL) {
          failf(data, "Syntax error in SFTP command. Supply parameter(s)!");
          state(conn, SSH_SFTP_CLOSE);
          sshc->nextstate = SSH_NO_STATE;
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
          sshc->nextstate = SSH_NO_STATE;
          sshc->actualcode = result;
          break;
        }

        /*
         * SFTP is a binary protocol, so we don't send text commands
         * to the server. Instead, we scan for commands used by
         * OpenSSH's sftp program and call the appropriate libssh2
         * functions.
         */
        if(curl_strnequal(cmd, "chgrp ", 6) ||
           curl_strnequal(cmd, "chmod ", 6) ||
           curl_strnequal(cmd, "chown ", 6) ) {
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
            state(conn, SSH_SFTP_CLOSE);
            sshc->nextstate = SSH_NO_STATE;
            sshc->actualcode = result;
            break;
          }
          memset(&sshc->quote_attrs, 0, sizeof(LIBSSH2_SFTP_ATTRIBUTES));
          state(conn, SSH_SFTP_QUOTE_STAT);
          break;
        }
        else if(curl_strnequal(cmd, "ln ", 3) ||
                curl_strnequal(cmd, "symlink ", 8)) {
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
            state(conn, SSH_SFTP_CLOSE);
            sshc->nextstate = SSH_NO_STATE;
            sshc->actualcode = result;
            break;
          }
          state(conn, SSH_SFTP_QUOTE_SYMLINK);
          break;
        }
        else if(curl_strnequal(cmd, "mkdir ", 6)) {
          /* create dir */
          state(conn, SSH_SFTP_QUOTE_MKDIR);
          break;
        }
        else if(curl_strnequal(cmd, "rename ", 7)) {
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
            state(conn, SSH_SFTP_CLOSE);
            sshc->nextstate = SSH_NO_STATE;
            sshc->actualcode = result;
            break;
          }
          state(conn, SSH_SFTP_QUOTE_RENAME);
          break;
        }
        else if(curl_strnequal(cmd, "rmdir ", 6)) {
          /* delete dir */
          state(conn, SSH_SFTP_QUOTE_RMDIR);
          break;
        }
        else if(curl_strnequal(cmd, "rm ", 3)) {
          state(conn, SSH_SFTP_QUOTE_UNLINK);
          break;
        }

        failf(data, "Unknown SFTP command");
        Curl_safefree(sshc->quote_path1);
        Curl_safefree(sshc->quote_path2);
        state(conn, SSH_SFTP_CLOSE);
        sshc->nextstate = SSH_NO_STATE;
        sshc->actualcode = CURLE_QUOTE_ERROR;
        break;
      }
    }
    if(!sshc->quote_item) {
      state(conn, SSH_SFTP_TRANS_INIT);
    }
    break;

    case SSH_SFTP_NEXT_QUOTE:
      Curl_safefree(sshc->quote_path1);
      Curl_safefree(sshc->quote_path2);

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
    {
      char *cmd = sshc->quote_item->data;
      sshc->acceptfail = FALSE;

      /* if a command starts with an asterisk, which a legal SFTP command never
         can, the command will be allowed to fail without it causing any
         aborts or cancels etc. It will cause libcurl to act as if the command
         is successful, whatever the server reponds. */

      if(cmd[0] == '*') {
        cmd++;
        sshc->acceptfail = TRUE;
      }

      if(!curl_strnequal(cmd, "chmod", 5)) {
        /* Since chown and chgrp only set owner OR group but libssh2 wants to
         * set them both at once, we need to obtain the current ownership
         * first.  This takes an extra protocol round trip.
         */
        rc = libssh2_sftp_stat_ex(sshc->sftp_session, sshc->quote_path2,
                                  curlx_uztoui(strlen(sshc->quote_path2)),
                                  LIBSSH2_SFTP_STAT,
                                  &sshc->quote_attrs);
        if(rc == LIBSSH2_ERROR_EAGAIN) {
          break;
        }
        else if(rc != 0 && !sshc->acceptfail) { /* get those attributes */
          err = sftp_libssh2_last_error(sshc->sftp_session);
          Curl_safefree(sshc->quote_path1);
          Curl_safefree(sshc->quote_path2);
          failf(data, "Attempt to get SFTP stats failed: %s",
                sftp_libssh2_strerror(err));
          state(conn, SSH_SFTP_CLOSE);
          sshc->nextstate = SSH_NO_STATE;
          sshc->actualcode = CURLE_QUOTE_ERROR;
          break;
        }
      }

      /* Now set the new attributes... */
      if(curl_strnequal(cmd, "chgrp", 5)) {
        sshc->quote_attrs.gid = strtoul(sshc->quote_path1, NULL, 10);
        sshc->quote_attrs.flags = LIBSSH2_SFTP_ATTR_UIDGID;
        if(sshc->quote_attrs.gid == 0 && !ISDIGIT(sshc->quote_path1[0]) &&
           !sshc->acceptfail) {
          Curl_safefree(sshc->quote_path1);
          Curl_safefree(sshc->quote_path2);
          failf(data, "Syntax error: chgrp gid not a number");
          state(conn, SSH_SFTP_CLOSE);
          sshc->nextstate = SSH_NO_STATE;
          sshc->actualcode = CURLE_QUOTE_ERROR;
          break;
        }
      }
      else if(curl_strnequal(cmd, "chmod", 5)) {
        sshc->quote_attrs.permissions = strtoul(sshc->quote_path1, NULL, 8);
        sshc->quote_attrs.flags = LIBSSH2_SFTP_ATTR_PERMISSIONS;
        /* permissions are octal */
        if(sshc->quote_attrs.permissions == 0 &&
           !ISDIGIT(sshc->quote_path1[0])) {
          Curl_safefree(sshc->quote_path1);
          Curl_safefree(sshc->quote_path2);
          failf(data, "Syntax error: chmod permissions not a number");
          state(conn, SSH_SFTP_CLOSE);
          sshc->nextstate = SSH_NO_STATE;
          sshc->actualcode = CURLE_QUOTE_ERROR;
          break;
        }
      }
      else if(curl_strnequal(cmd, "chown", 5)) {
        sshc->quote_attrs.uid = strtoul(sshc->quote_path1, NULL, 10);
        sshc->quote_attrs.flags = LIBSSH2_SFTP_ATTR_UIDGID;
        if(sshc->quote_attrs.uid == 0 && !ISDIGIT(sshc->quote_path1[0]) &&
           !sshc->acceptfail) {
          Curl_safefree(sshc->quote_path1);
          Curl_safefree(sshc->quote_path2);
          failf(data, "Syntax error: chown uid not a number");
          state(conn, SSH_SFTP_CLOSE);
          sshc->nextstate = SSH_NO_STATE;
          sshc->actualcode = CURLE_QUOTE_ERROR;
          break;
        }
      }

      /* Now send the completed structure... */
      state(conn, SSH_SFTP_QUOTE_SETSTAT);
      break;
    }

    case SSH_SFTP_QUOTE_SETSTAT:
      rc = libssh2_sftp_stat_ex(sshc->sftp_session, sshc->quote_path2,
                                curlx_uztoui(strlen(sshc->quote_path2)),
                                LIBSSH2_SFTP_SETSTAT,
                                &sshc->quote_attrs);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc != 0 && !sshc->acceptfail) {
        err = sftp_libssh2_last_error(sshc->sftp_session);
        Curl_safefree(sshc->quote_path1);
        Curl_safefree(sshc->quote_path2);
        failf(data, "Attempt to set SFTP stats failed: %s",
              sftp_libssh2_strerror(err));
        state(conn, SSH_SFTP_CLOSE);
        sshc->nextstate = SSH_NO_STATE;
        sshc->actualcode = CURLE_QUOTE_ERROR;
        break;
      }
      state(conn, SSH_SFTP_NEXT_QUOTE);
      break;

    case SSH_SFTP_QUOTE_SYMLINK:
      rc = libssh2_sftp_symlink_ex(sshc->sftp_session, sshc->quote_path1,
                                   curlx_uztoui(strlen(sshc->quote_path1)),
                                   sshc->quote_path2,
                                   curlx_uztoui(strlen(sshc->quote_path2)),
                                   LIBSSH2_SFTP_SYMLINK);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc != 0 && !sshc->acceptfail) {
        err = sftp_libssh2_last_error(sshc->sftp_session);
        Curl_safefree(sshc->quote_path1);
        Curl_safefree(sshc->quote_path2);
        failf(data, "symlink command failed: %s",
              sftp_libssh2_strerror(err));
        state(conn, SSH_SFTP_CLOSE);
        sshc->nextstate = SSH_NO_STATE;
        sshc->actualcode = CURLE_QUOTE_ERROR;
        break;
      }
      state(conn, SSH_SFTP_NEXT_QUOTE);
      break;

    case SSH_SFTP_QUOTE_MKDIR:
      rc = libssh2_sftp_mkdir_ex(sshc->sftp_session, sshc->quote_path1,
                                 curlx_uztoui(strlen(sshc->quote_path1)),
                                 data->set.new_directory_perms);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc != 0 && !sshc->acceptfail) {
        err = sftp_libssh2_last_error(sshc->sftp_session);
        Curl_safefree(sshc->quote_path1);
        failf(data, "mkdir command failed: %s", sftp_libssh2_strerror(err));
        state(conn, SSH_SFTP_CLOSE);
        sshc->nextstate = SSH_NO_STATE;
        sshc->actualcode = CURLE_QUOTE_ERROR;
        break;
      }
      state(conn, SSH_SFTP_NEXT_QUOTE);
      break;

    case SSH_SFTP_QUOTE_RENAME:
      rc = libssh2_sftp_rename_ex(sshc->sftp_session, sshc->quote_path1,
                                  curlx_uztoui(strlen(sshc->quote_path1)),
                                  sshc->quote_path2,
                                  curlx_uztoui(strlen(sshc->quote_path2)),
                                  LIBSSH2_SFTP_RENAME_OVERWRITE |
                                  LIBSSH2_SFTP_RENAME_ATOMIC |
                                  LIBSSH2_SFTP_RENAME_NATIVE);

      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc != 0 && !sshc->acceptfail) {
        err = sftp_libssh2_last_error(sshc->sftp_session);
        Curl_safefree(sshc->quote_path1);
        Curl_safefree(sshc->quote_path2);
        failf(data, "rename command failed: %s", sftp_libssh2_strerror(err));
        state(conn, SSH_SFTP_CLOSE);
        sshc->nextstate = SSH_NO_STATE;
        sshc->actualcode = CURLE_QUOTE_ERROR;
        break;
      }
      state(conn, SSH_SFTP_NEXT_QUOTE);
      break;

    case SSH_SFTP_QUOTE_RMDIR:
      rc = libssh2_sftp_rmdir_ex(sshc->sftp_session, sshc->quote_path1,
                                 curlx_uztoui(strlen(sshc->quote_path1)));
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc != 0 && !sshc->acceptfail) {
        err = sftp_libssh2_last_error(sshc->sftp_session);
        Curl_safefree(sshc->quote_path1);
        failf(data, "rmdir command failed: %s", sftp_libssh2_strerror(err));
        state(conn, SSH_SFTP_CLOSE);
        sshc->nextstate = SSH_NO_STATE;
        sshc->actualcode = CURLE_QUOTE_ERROR;
        break;
      }
      state(conn, SSH_SFTP_NEXT_QUOTE);
      break;

    case SSH_SFTP_QUOTE_UNLINK:
      rc = libssh2_sftp_unlink_ex(sshc->sftp_session, sshc->quote_path1,
                                  curlx_uztoui(strlen(sshc->quote_path1)));
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc != 0 && !sshc->acceptfail) {
        err = sftp_libssh2_last_error(sshc->sftp_session);
        Curl_safefree(sshc->quote_path1);
        failf(data, "rm command failed: %s", sftp_libssh2_strerror(err));
        state(conn, SSH_SFTP_CLOSE);
        sshc->nextstate = SSH_NO_STATE;
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
    {
      unsigned long flags;
      /*
       * NOTE!!!  libssh2 requires that the destination path is a full path
       *          that includes the destination file and name OR ends in a "/"
       *          If this is not done the destination file will be named the
       *          same name as the last directory in the path.
       */

      if(data->state.resume_from != 0) {
        LIBSSH2_SFTP_ATTRIBUTES attrs;
        if(data->state.resume_from < 0) {
          rc = libssh2_sftp_stat_ex(sshc->sftp_session, sftp_scp->path,
                                    curlx_uztoui(strlen(sftp_scp->path)),
                                    LIBSSH2_SFTP_STAT, &attrs);
          if(rc == LIBSSH2_ERROR_EAGAIN) {
            break;
          }
          else if(rc) {
            data->state.resume_from = 0;
          }
          else {
            curl_off_t size = attrs.filesize;
            if(size < 0) {
              failf(data, "Bad file size (%" CURL_FORMAT_CURL_OFF_T ")", size);
              return CURLE_BAD_DOWNLOAD_RESUME;
            }
            data->state.resume_from = attrs.filesize;
          }
        }
      }

      if(data->set.ftp_append)
        /* Try to open for append, but create if nonexisting */
        flags = LIBSSH2_FXF_WRITE|LIBSSH2_FXF_CREAT|LIBSSH2_FXF_APPEND;
      else if(data->state.resume_from > 0)
        /* If we have restart position then open for append */
        flags = LIBSSH2_FXF_WRITE|LIBSSH2_FXF_APPEND;
      else
        /* Clear file before writing (normal behaviour) */
        flags = LIBSSH2_FXF_WRITE|LIBSSH2_FXF_CREAT|LIBSSH2_FXF_TRUNC;

      sshc->sftp_handle =
        libssh2_sftp_open_ex(sshc->sftp_session, sftp_scp->path,
                             curlx_uztoui(strlen(sftp_scp->path)),
                             flags, data->set.new_file_perms,
                             LIBSSH2_SFTP_OPENFILE);

      if(!sshc->sftp_handle) {
        rc = libssh2_session_last_errno(sshc->ssh_session);

        if(LIBSSH2_ERROR_EAGAIN == rc)
          break;
        else {
          if(LIBSSH2_ERROR_SFTP_PROTOCOL == rc)
            /* only when there was an SFTP protocol error can we extract
               the sftp error! */
            err = sftp_libssh2_last_error(sshc->sftp_session);
          else
            err = -1; /* not an sftp error at all */

          if(sshc->secondCreateDirs) {
            state(conn, SSH_SFTP_CLOSE);
            sshc->actualcode = err>= LIBSSH2_FX_OK?
              sftp_libssh2_error_to_CURLE(err):CURLE_SSH;
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
          sshc->actualcode = err>= LIBSSH2_FX_OK?
            sftp_libssh2_error_to_CURLE(err):CURLE_SSH;
          if(!sshc->actualcode) {
            /* Sometimes, for some reason libssh2_sftp_last_error() returns
               zero even though libssh2_sftp_open() failed previously! We need
               to work around that! */
            sshc->actualcode = CURLE_SSH;
            err=-1;
          }
          failf(data, "Upload failed: %s (%d/%d)",
                err>= LIBSSH2_FX_OK?sftp_libssh2_strerror(err):"ssh error",
                err, rc);
          break;
        }
      }

      /* If we have a restart point then we need to seek to the correct
         position. */
      if(data->state.resume_from > 0) {
        /* Let's read off the proper amount of bytes from the input. */
        if(conn->seek_func) {
          seekerr = conn->seek_func(conn->seek_client, data->state.resume_from,
                                    SEEK_SET);
        }

        if(seekerr != CURL_SEEKFUNC_OK) {

          if(seekerr != CURL_SEEKFUNC_CANTSEEK) {
            failf(data, "Could not seek stream");
            return CURLE_FTP_COULDNT_USE_REST;
          }
          /* seekerr == CURL_SEEKFUNC_CANTSEEK (can't seek to offset) */
          else {
            curl_off_t passed=0;
            do {
              size_t readthisamountnow =
                (data->state.resume_from - passed > CURL_OFF_T_C(BUFSIZE)) ?
                BUFSIZE : curlx_sotouz(data->state.resume_from - passed);

              size_t actuallyread =
                conn->fread_func(data->state.buffer, 1, readthisamountnow,
                                 conn->fread_in);

              passed += actuallyread;
              if((actuallyread == 0) || (actuallyread > readthisamountnow)) {
                /* this checks for greater-than only to make sure that the
                   CURL_READFUNC_ABORT return code still aborts */
                failf(data, "Failed to read data");
                return CURLE_FTP_COULDNT_USE_REST;
              }
            } while(passed < data->state.resume_from);
          }
        }

        /* now, decrease the size of the read */
        if(data->state.infilesize > 0) {
          data->state.infilesize -= data->state.resume_from;
          data->req.size = data->state.infilesize;
          Curl_pgrsSetUploadSize(data, data->state.infilesize);
        }

        SFTP_SEEK(sshc->sftp_handle, data->state.resume_from);
      }
      if(data->state.infilesize > 0) {
        data->req.size = data->state.infilesize;
        Curl_pgrsSetUploadSize(data, data->state.infilesize);
      }
      /* upload data */
      Curl_setup_transfer(conn, -1, -1, FALSE, NULL, FIRSTSOCKET, NULL);

      /* not set by Curl_setup_transfer to preserve keepon bits */
      conn->sockfd = conn->writesockfd;

      if(result) {
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = result;
      }
      else {
        /* store this original bitmask setup to use later on if we can't
           figure out a "real" bitmask */
        sshc->orig_waitfor = data->req.keepon;

        /* we want to use the _sending_ function even when the socket turns
           out readable as the underlying libssh2 sftp send function will deal
           with both accordingly */
        conn->cselect_bits = CURL_CSELECT_OUT;

        /* since we don't really wait for anything at this point, we want the
           state machine to move on as soon as possible so we set a very short
           timeout here */
        Curl_expire(data, 1);

        state(conn, SSH_STOP);
      }
      break;
    }

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
      sshc->slash_pos = strchr(sshc->slash_pos, '/');
      if(sshc->slash_pos) {
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
      rc = libssh2_sftp_mkdir_ex(sshc->sftp_session, sftp_scp->path,
                                 curlx_uztoui(strlen(sftp_scp->path)),
                                 data->set.new_directory_perms);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      *sshc->slash_pos = '/';
      ++sshc->slash_pos;
      if(rc == -1) {
        /*
         * Abort if failure wasn't that the dir already exists or the
         * permission was denied (creation might succeed further down the
         * path) - retry on unspecific FAILURE also
         */
        err = sftp_libssh2_last_error(sshc->sftp_session);
        if((err != LIBSSH2_FX_FILE_ALREADY_EXISTS) &&
           (err != LIBSSH2_FX_FAILURE) &&
           (err != LIBSSH2_FX_PERMISSION_DENIED)) {
          result = sftp_libssh2_error_to_CURLE(err);
          state(conn, SSH_SFTP_CLOSE);
          sshc->actualcode = result?result:CURLE_SSH;
          break;
        }
      }
      state(conn, SSH_SFTP_CREATE_DIRS);
      break;

    case SSH_SFTP_READDIR_INIT:
      Curl_pgrsSetDownloadSize(data, -1);
      if(data->set.opt_no_body) {
        state(conn, SSH_STOP);
        break;
      }

      /*
       * This is a directory that we are trying to get, so produce a directory
       * listing
       */
      sshc->sftp_handle = libssh2_sftp_open_ex(sshc->sftp_session,
                                               sftp_scp->path,
                                               curlx_uztoui(
                                                 strlen(sftp_scp->path)),
                                               0, 0, LIBSSH2_SFTP_OPENDIR);
      if(!sshc->sftp_handle) {
        if(libssh2_session_last_errno(sshc->ssh_session) ==
           LIBSSH2_ERROR_EAGAIN) {
          rc = LIBSSH2_ERROR_EAGAIN;
          break;
        }
        else {
          err = sftp_libssh2_last_error(sshc->sftp_session);
          failf(data, "Could not open directory for reading: %s",
                sftp_libssh2_strerror(err));
          state(conn, SSH_SFTP_CLOSE);
          result = sftp_libssh2_error_to_CURLE(err);
          sshc->actualcode = result?result:CURLE_SSH;
          break;
        }
      }
      if((sshc->readdir_filename = malloc(PATH_MAX+1)) == NULL) {
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = CURLE_OUT_OF_MEMORY;
        break;
      }
      if((sshc->readdir_longentry = malloc(PATH_MAX+1)) == NULL) {
        Curl_safefree(sshc->readdir_filename);
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
        rc = LIBSSH2_ERROR_EAGAIN;
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
          /* since this counts what we send to the client, we include the
             newline in this counter */
          data->req.bytecount += sshc->readdir_len+1;

          /* output debug output if that is requested */
          if(data->set.verbose) {
            Curl_debug(data, CURLINFO_DATA_OUT, sshc->readdir_filename,
                       sshc->readdir_len, conn);
          }
        }
        else {
          sshc->readdir_currLen = (int)strlen(sshc->readdir_longentry);
          sshc->readdir_totalLen = 80 + sshc->readdir_currLen;
          sshc->readdir_line = calloc(sshc->readdir_totalLen, 1);
          if(!sshc->readdir_line) {
            Curl_safefree(sshc->readdir_filename);
            Curl_safefree(sshc->readdir_longentry);
            state(conn, SSH_SFTP_CLOSE);
            sshc->actualcode = CURLE_OUT_OF_MEMORY;
            break;
          }

          memcpy(sshc->readdir_line, sshc->readdir_longentry,
                 sshc->readdir_currLen);
          if((sshc->readdir_attrs.flags & LIBSSH2_SFTP_ATTR_PERMISSIONS) &&
             ((sshc->readdir_attrs.permissions & LIBSSH2_SFTP_S_IFMT) ==
              LIBSSH2_SFTP_S_IFLNK)) {
            sshc->readdir_linkPath = malloc(PATH_MAX + 1);
            if(sshc->readdir_linkPath == NULL) {
              Curl_safefree(sshc->readdir_filename);
              Curl_safefree(sshc->readdir_longentry);
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
        Curl_safefree(sshc->readdir_longentry);
        state(conn, SSH_SFTP_READDIR_DONE);
        break;
      }
      else if(sshc->readdir_len <= 0) {
        err = sftp_libssh2_last_error(sshc->sftp_session);
        result = sftp_libssh2_error_to_CURLE(err);
        sshc->actualcode = result?result:CURLE_SSH;
        failf(data, "Could not open remote file for reading: %s :: %d",
              sftp_libssh2_strerror(err),
              libssh2_session_last_errno(sshc->ssh_session));
        Curl_safefree(sshc->readdir_filename);
        Curl_safefree(sshc->readdir_longentry);
        state(conn, SSH_SFTP_CLOSE);
        break;
      }
      break;

    case SSH_SFTP_READDIR_LINK:
      sshc->readdir_len =
        libssh2_sftp_symlink_ex(sshc->sftp_session,
                                sshc->readdir_linkPath,
                                curlx_uztoui(strlen(sshc->readdir_linkPath)),
                                sshc->readdir_filename,
                                PATH_MAX, LIBSSH2_SFTP_READLINK);
      if(sshc->readdir_len == LIBSSH2_ERROR_EAGAIN) {
        rc = LIBSSH2_ERROR_EAGAIN;
        break;
      }
      Curl_safefree(sshc->readdir_linkPath);

      /* get room for the filename and extra output */
      sshc->readdir_totalLen += 4 + sshc->readdir_len;
      new_readdir_line = realloc(sshc->readdir_line, sshc->readdir_totalLen);
      if(!new_readdir_line) {
        Curl_safefree(sshc->readdir_line);
        Curl_safefree(sshc->readdir_filename);
        Curl_safefree(sshc->readdir_longentry);
        state(conn, SSH_SFTP_CLOSE);
        sshc->actualcode = CURLE_OUT_OF_MEMORY;
        break;
      }
      sshc->readdir_line = new_readdir_line;

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

      if(!result) {

        /* output debug output if that is requested */
        if(data->set.verbose) {
          Curl_debug(data, CURLINFO_DATA_OUT, sshc->readdir_line,
                     sshc->readdir_currLen, conn);
        }
        data->req.bytecount += sshc->readdir_currLen;
      }
      Curl_safefree(sshc->readdir_line);
      if(result) {
        state(conn, SSH_STOP);
      }
      else
        state(conn, SSH_SFTP_READDIR);
      break;

    case SSH_SFTP_READDIR_DONE:
      if(libssh2_sftp_closedir(sshc->sftp_handle) ==
         LIBSSH2_ERROR_EAGAIN) {
        rc = LIBSSH2_ERROR_EAGAIN;
        break;
      }
      sshc->sftp_handle = NULL;
      Curl_safefree(sshc->readdir_filename);
      Curl_safefree(sshc->readdir_longentry);

      /* no data to transfer */
      Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
      state(conn, SSH_STOP);
      break;

    case SSH_SFTP_DOWNLOAD_INIT:
      /*
       * Work on getting the specified file
       */
      sshc->sftp_handle =
        libssh2_sftp_open_ex(sshc->sftp_session, sftp_scp->path,
                             curlx_uztoui(strlen(sftp_scp->path)),
                             LIBSSH2_FXF_READ, data->set.new_file_perms,
                             LIBSSH2_SFTP_OPENFILE);
      if(!sshc->sftp_handle) {
        if(libssh2_session_last_errno(sshc->ssh_session) ==
           LIBSSH2_ERROR_EAGAIN) {
          rc = LIBSSH2_ERROR_EAGAIN;
          break;
        }
        else {
          err = sftp_libssh2_last_error(sshc->sftp_session);
          failf(data, "Could not open remote file for reading: %s",
                sftp_libssh2_strerror(err));
          state(conn, SSH_SFTP_CLOSE);
          result = sftp_libssh2_error_to_CURLE(err);
          sshc->actualcode = result?result:CURLE_SSH;
          break;
        }
      }
      state(conn, SSH_SFTP_DOWNLOAD_STAT);
      break;

    case SSH_SFTP_DOWNLOAD_STAT:
    {
      LIBSSH2_SFTP_ATTRIBUTES attrs;

      rc = libssh2_sftp_stat_ex(sshc->sftp_session, sftp_scp->path,
                                curlx_uztoui(strlen(sftp_scp->path)),
                                LIBSSH2_SFTP_STAT, &attrs);
      if(rc == LIBSSH2_ERROR_EAGAIN) {
        break;
      }
      else if(rc ||
              !(attrs.flags & LIBSSH2_SFTP_ATTR_SIZE) ||
              (attrs.filesize == 0)) {
        /*
         * libssh2_sftp_open() didn't return an error, so maybe the server
         * just doesn't support stat()
         * OR the server doesn't return a file size with a stat()
         * OR file size is 0
         */
        data->req.size = -1;
        data->req.maxdownload = -1;
        Curl_pgrsSetDownloadSize(data, -1);
      }
      else {
        curl_off_t size = attrs.filesize;

        if(size < 0) {
          failf(data, "Bad file size (%" CURL_FORMAT_CURL_OFF_T ")", size);
          return CURLE_BAD_DOWNLOAD_RESUME;
        }
        if(conn->data->state.use_range) {
          curl_off_t from, to;
          char *ptr;
          char *ptr2;

          from=curlx_strtoofft(conn->data->state.range, &ptr, 0);
          while(*ptr && (ISSPACE(*ptr) || (*ptr=='-')))
            ptr++;
          to=curlx_strtoofft(ptr, &ptr2, 0);
          if((ptr == ptr2) /* no "to" value given */
             || (to >= size)) {
            to = size - 1;
          }
          if(from < 0) {
            /* from is relative to end of file */
            from += size;
          }
          if(from >= size) {
            failf(data, "Offset (%"
                  CURL_FORMAT_CURL_OFF_T ") was beyond file size (%"
                  CURL_FORMAT_CURL_OFF_T ")", from, attrs.filesize);
            return CURLE_BAD_DOWNLOAD_RESUME;
          }
          if(from > to) {
            from = to;
            size = 0;
          }
          else {
            size = to - from + 1;
          }

          SFTP_SEEK(conn->proto.sshc.sftp_handle, from);
        }
        data->req.size = size;
        data->req.maxdownload = size;
        Curl_pgrsSetDownloadSize(data, size);
      }

      /* We can resume if we can seek to the resume position */
      if(data->state.resume_from) {
        if(data->state.resume_from < 0) {
          /* We're supposed to download the last abs(from) bytes */
          if((curl_off_t)attrs.filesize < -data->state.resume_from) {
            failf(data, "Offset (%"
                  CURL_FORMAT_CURL_OFF_T ") was beyond file size (%"
                  CURL_FORMAT_CURL_OFF_T ")",
                  data->state.resume_from, attrs.filesize);
            return CURLE_BAD_DOWNLOAD_RESUME;
          }
          /* download from where? */
          data->state.resume_from += attrs.filesize;
        }
        else {
          if((curl_off_t)attrs.filesize < data->state.resume_from) {
            failf(data, "Offset (%" CURL_FORMAT_CURL_OFF_T
                  ") was beyond file size (%" CURL_FORMAT_CURL_OFF_T ")",
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
        SFTP_SEEK(sshc->sftp_handle, data->state.resume_from);
      }
    }

    /* Setup the actual download */
    if(data->req.size == 0) {
      /* no data to transfer */
      Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
      infof(data, "File already completely downloaded\n");
      state(conn, SSH_STOP);
      break;
    }
    else {
      Curl_setup_transfer(conn, FIRSTSOCKET, data->req.size,
                          FALSE, NULL, -1, NULL);

      /* not set by Curl_setup_transfer to preserve keepon bits */
      conn->writesockfd = conn->sockfd;

      /* we want to use the _receiving_ function even when the socket turns
         out writableable as the underlying libssh2 recv function will deal
         with both accordingly */
      conn->cselect_bits = CURL_CSELECT_IN;
    }
    if(result) {
      /* this should never occur; the close state should be entered
         at the time the error occurs */
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
      if(sftp_scp)
        Curl_safefree(sftp_scp->path);

      DEBUGF(infof(data, "SFTP DONE done\n"));

      /* Check if nextstate is set and move .nextstate could be POSTQUOTE_INIT
         After nextstate is executed,the control should come back to
         SSH_SFTP_CLOSE to pass the correct result back  */
      if(sshc->nextstate != SSH_NO_STATE &&
         sshc->nextstate != SSH_SFTP_CLOSE) {
        state(conn, sshc->nextstate);
        sshc->nextstate = SSH_SFTP_CLOSE;
      }
      else {
        state(conn, SSH_STOP);
        result = sshc->actualcode;
      }
      break;

    case SSH_SFTP_SHUTDOWN:
      /* during times we get here due to a broken transfer and then the
         sftp_handle might not have been taken down so make sure that is done
         before we proceed */

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
      conn->data->state.most_recent_ftp_entrypath = NULL;

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
        if(data->state.infilesize < 0) {
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
        SCP_SEND(sshc->ssh_session, sftp_scp->path, data->set.new_file_perms,
                 data->state.infilesize);
      if(!sshc->ssh_channel) {
        if(libssh2_session_last_errno(sshc->ssh_session) ==
           LIBSSH2_ERROR_EAGAIN) {
          rc = LIBSSH2_ERROR_EAGAIN;
          break;
        }
        else {
          int ssh_err;
          char *err_msg;

          ssh_err = (int)(libssh2_session_last_error(sshc->ssh_session,
                                                     &err_msg, NULL, 0));
          failf(conn->data, "%s", err_msg);
          state(conn, SSH_SCP_CHANNEL_FREE);
          sshc->actualcode = libssh2_session_error_to_CURLE(ssh_err);
          break;
        }
      }

      /* upload data */
      Curl_setup_transfer(conn, -1, data->req.size, FALSE, NULL,
                          FIRSTSOCKET, NULL);

      /* not set by Curl_setup_transfer to preserve keepon bits */
      conn->sockfd = conn->writesockfd;

      if(result) {
        state(conn, SSH_SCP_CHANNEL_FREE);
        sshc->actualcode = result;
      }
      else {
        /* store this original bitmask setup to use later on if we can't
           figure out a "real" bitmask */
        sshc->orig_waitfor = data->req.keepon;

        /* we want to use the _sending_ function even when the socket turns
           out readable as the underlying libssh2 scp send function will deal
           with both accordingly */
        conn->cselect_bits = CURL_CSELECT_OUT;

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
          rc = LIBSSH2_ERROR_EAGAIN;
          break;
        }
        else {
          int ssh_err;
          char *err_msg;

          ssh_err = (int)(libssh2_session_last_error(sshc->ssh_session,
                                                     &err_msg, NULL, 0));
          failf(conn->data, "%s", err_msg);
          state(conn, SSH_SCP_CHANNEL_FREE);
          sshc->actualcode = libssh2_session_error_to_CURLE(ssh_err);
          break;
        }
      }

      /* download data */
      bytecount = (curl_off_t)sb.st_size;
      data->req.maxdownload =  (curl_off_t)sb.st_size;
      Curl_setup_transfer(conn, FIRSTSOCKET, bytecount, FALSE, NULL, -1, NULL);

      /* not set by Curl_setup_transfer to preserve keepon bits */
      conn->writesockfd = conn->sockfd;

      /* we want to use the _receiving_ function even when the socket turns
         out writableable as the underlying libssh2 recv function will deal
         with both accordingly */
      conn->cselect_bits = CURL_CSELECT_IN;

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
      /* during weird times when we've been prematurely aborted, the channel
         is still alive when we reach this state and we MUST kill the channel
         properly first */
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
      conn->data->state.most_recent_ftp_entrypath = NULL;

      state(conn, SSH_SESSION_FREE);
      break;

    case SSH_SESSION_FREE:
#ifdef HAVE_LIBSSH2_KNOWNHOST_API
      if(sshc->kh) {
        libssh2_knownhost_free(sshc->kh);
        sshc->kh = NULL;
      }
#endif

#ifdef HAVE_LIBSSH2_AGENT_API
      if(sshc->ssh_agent) {
        rc = libssh2_agent_disconnect(sshc->ssh_agent);
        if(rc == LIBSSH2_ERROR_EAGAIN) {
          break;
        }
        else if(rc < 0) {
          infof(data, "Failed to disconnect from libssh2 agent\n");
        }
        libssh2_agent_free (sshc->ssh_agent);
        sshc->ssh_agent = NULL;

        /* NB: there is no need to free identities, they are part of internal
           agent stuff */
        sshc->sshagent_identity = NULL;
        sshc->sshagent_prev_identity = NULL;
      }
#endif

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

      /* worst-case scenario cleanup */

      DEBUGASSERT(sshc->ssh_session == NULL);
      DEBUGASSERT(sshc->ssh_channel == NULL);
      DEBUGASSERT(sshc->sftp_session == NULL);
      DEBUGASSERT(sshc->sftp_handle == NULL);
#ifdef HAVE_LIBSSH2_KNOWNHOST_API
      DEBUGASSERT(sshc->kh == NULL);
#endif
#ifdef HAVE_LIBSSH2_AGENT_API
      DEBUGASSERT(sshc->ssh_agent == NULL);
#endif

      Curl_safefree(sshc->rsa_pub);
      Curl_safefree(sshc->rsa);

      Curl_safefree(sshc->quote_path1);
      Curl_safefree(sshc->quote_path2);

      Curl_safefree(sshc->homedir);

      Curl_safefree(sshc->readdir_filename);
      Curl_safefree(sshc->readdir_longentry);
      Curl_safefree(sshc->readdir_line);
      Curl_safefree(sshc->readdir_linkPath);

      /* the code we are about to return */
      result = sshc->actualcode;

      memset(sshc, 0, sizeof(struct ssh_conn));

      connclose(conn, "SSH session free");
      sshc->state = SSH_SESSION_FREE; /* current */
      sshc->nextstate = SSH_NO_STATE;
      state(conn, SSH_STOP);
      break;

    case SSH_QUIT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      sshc->nextstate = SSH_NO_STATE;
      state(conn, SSH_STOP);
      break;
    }

  } while(!rc && (sshc->state != SSH_STOP));

  if(rc == LIBSSH2_ERROR_EAGAIN) {
    /* we would block, we need to wait for the socket to be ready (in the
       right direction too)! */
    *block = TRUE;
  }

  return result;
}