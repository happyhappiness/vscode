failf(data, "schannel: next InitializeSecurityContext failed: %s",
              Curl_sspi_strerror(conn, sspi_status))