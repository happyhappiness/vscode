warnf(config->global, "ignoring %s, not supported by libcurl\n",
                  capath_from_env?
                  "SSL_CERT_DIR environment variable":"--capath");