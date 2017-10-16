          }
          infdopen=TRUE;
          uploadfilesize=fileinfo.st_size;

        }
        else if(uploadfile && stdin_upload(uploadfile)) {
          SET_BINMODE(stdin);
          infd = STDIN_FILENO;
          if (curlx_strequal(uploadfile, ".")) {
            if (curlx_nonblock((curl_socket_t)infd, TRUE) < 0)
              warnf(config,
                    "fcntl failed on fd=%d: %s\n", infd, strerror(errno));
