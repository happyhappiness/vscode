          my_setopt_str(curl, CURLOPT_SSH_HOST_PUBLIC_KEY_MD5,
                        config->hostpubmd5);
        }

        if(config->cacert)
          my_setopt_str(curl, CURLOPT_CAINFO, config->cacert);
        if(config->capath) {
          result = res_setopt_str(curl, CURLOPT_CAPATH, config->capath);
          if(result == CURLE_NOT_BUILT_IN) {
            warnf(config->global, "ignoring %s, not supported by libcurl\n",
                  capath_from_env?
                  "SSL_CERT_DIR environment variable":"--capath");
          }
          else if(result)
            goto show_error;
        }
        if(config->crlfile)
          my_setopt_str(curl, CURLOPT_CRLFILE, config->crlfile);

        if(config->pinnedpubkey)
          my_setopt_str(curl, CURLOPT_PINNEDPUBLICKEY, config->pinnedpubkey);

