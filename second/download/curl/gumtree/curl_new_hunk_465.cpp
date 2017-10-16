          }
          infdopen=TRUE;
          uploadfilesize=fileinfo.st_size;

        }
        else if(uploadfile && stdin_upload(uploadfile)) {
          /* count to see if there are more than one auth bit set
             in the authtype field */
          int authbits = 0;
          int bitcheck = 0;
          while(bitcheck < 32) {
            if(config->authtype & (1 << bitcheck++)) {
              authbits++;
              if(authbits > 1) {
                /* more than one, we're done! */
                break;
              }
            }
          }

          /*
           * If the user has also selected --anyauth or --proxy-anyauth
           * we should warn him/her.
           */
          if(config->proxyanyauth || (authbits>1)) {
            warnf(config,
                  "Using --anyauth or --proxy-anyauth with upload from stdin"
                  " involves a big risk of it not working. Use a temporary"
                  " file or a fixed auth type instead!\n");
          }

          SET_BINMODE(stdin);
          infd = STDIN_FILENO;
          if (curlx_strequal(uploadfile, ".")) {
            if (curlx_nonblock((curl_socket_t)infd, TRUE) < 0)
              warnf(config,
                    "fcntl failed on fd=%d: %s\n", infd, strerror(errno));
