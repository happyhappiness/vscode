fatalf("SSL private key '%s' does not match public key '%s': %s\n",
                   certfile, keyfile, ERR_error_string(ssl_error, NULL));