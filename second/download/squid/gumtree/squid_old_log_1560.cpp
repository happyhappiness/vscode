fatalf("Failed to acquire SSL certificate '%s': %s\n",
                   certfile, ERR_error_string(ssl_error, NULL));