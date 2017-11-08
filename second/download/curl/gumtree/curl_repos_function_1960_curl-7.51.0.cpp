static int check_sspi_err(struct connectdata *conn,
                          SECURITY_STATUS status,
                          const char* function)
{
  if(status != SEC_E_OK &&
     status != SEC_I_COMPLETE_AND_CONTINUE &&
     status != SEC_I_COMPLETE_NEEDED &&
     status != SEC_I_CONTINUE_NEEDED) {
    failf(conn->data, "SSPI error: %s failed: %s", function,
          Curl_sspi_strerror(conn, status));
    return 1;
  }
  return 0;
}