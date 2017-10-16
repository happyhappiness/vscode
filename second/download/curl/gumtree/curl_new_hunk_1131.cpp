          }

          DEBUGASSERT(infdopen == FALSE);
          DEBUGASSERT(infd == STDIN_FILENO);

          set_binmode(stdin);
          if(!strcmp(uploadfile, ".")) {
            if(curlx_nonblock((curl_socket_t)infd, TRUE) < 0)
              warnf(config->global,
                    "fcntl failed on fd=%d: %s\n", infd, strerror(errno));
          }
        }

