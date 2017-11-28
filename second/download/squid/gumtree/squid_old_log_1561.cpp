fatalf("Failed to acquire SSL private key '%s': %s\n",
                   keyfile, ERR_error_string(ssl_error, NULL));