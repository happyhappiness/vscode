
        lerr = SSL_get_verify_result(connssl->handle);
        if(lerr != X509_V_OK) {
          snprintf(error_buffer, sizeof(error_buffer),
                   "SSL certificate problem: %s",
                   X509_verify_cert_error_string(lerr));
