        sshc->acceptfail = TRUE;
      }

      if(curl_strequal("pwd", cmd)) {
        /* output debug output if that is requested */
        char *tmp = aprintf("257 \"%s\" is current directory.\n",
                            sftp_scp->path);
