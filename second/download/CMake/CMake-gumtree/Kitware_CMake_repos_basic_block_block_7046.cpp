failf(data, "schannel: AcquireCredentialsHandle failed: %s",
              Curl_sspi_strerror(conn, sspi_status))