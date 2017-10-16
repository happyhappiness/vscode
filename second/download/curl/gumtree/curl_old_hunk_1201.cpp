                  capath_from_env?
                  "SSL_CERT_DIR environment variable":"--capath");
          }
          else if(result)
            goto show_error;
        }
        if(config->proxy_capath)
          my_setopt_str(curl, CURLOPT_PROXY_CAPATH, config->proxy_capath);
        else if(config->capath) /* CURLOPT_PROXY_CAPATH default is capath */
          my_setopt_str(curl, CURLOPT_PROXY_CAPATH, config->capath);

        if(config->crlfile)
          my_setopt_str(curl, CURLOPT_CRLFILE, config->crlfile);
        if(config->proxy_crlfile)
          my_setopt_str(curl, CURLOPT_PROXY_CRLFILE, config->proxy_crlfile);
        else if(config->crlfile) /* CURLOPT_PROXY_CRLFILE default is crlfile */
