          uploadfilesize=fileinfo.st_size;

        }
        else if(uploadfile && curlx_strequal(uploadfile, "-")) {
          SET_BINMODE(stdin);
          infd = STDIN_FILENO;
        }

        if(uploadfile && config->resume_from_current)
          config->resume_from = -1; /* -1 will then force get-it-yourself */

        if(output_expected(url, uploadfile)
