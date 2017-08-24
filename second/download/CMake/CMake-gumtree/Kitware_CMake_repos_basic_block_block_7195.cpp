{
    failf(data, "schannel: Failed to read remote certificate context: %s",
          Curl_sspi_strerror(conn, status));
    result = CURLE_PEER_FAILED_VERIFICATION;
  }