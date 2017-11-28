fatalf("SSL private key '%s' does not match public key '%s': %s\n",
                       certfile, keyfile, Security::ErrorString(ssl_error));