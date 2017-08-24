{
    failf(conn->data, "SSPI error: %s failed: %s", function,
          Curl_sspi_strerror(conn, status));
    return 1;
  }