snprintf(error_buffer, sizeof(error_buffer),
                   "SSL certificate problem: %s",
                   X509_verify_cert_error_string(lerr));