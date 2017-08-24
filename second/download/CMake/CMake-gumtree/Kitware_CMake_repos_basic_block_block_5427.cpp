f(smtpc->tls_supported)
          /* Switch to TLS connection now */
          result = smtp_perform_starttls(conn);
        else if(data->set.use_ssl == CURLUSESSL_TRY)
          /* Fallback and carry on with authentication */
          result = smtp_perform_authentication(conn);
        else {
          failf(data, "STARTTLS not supported.");
          result = CURLE_USE_SSL_FAILED;
        }