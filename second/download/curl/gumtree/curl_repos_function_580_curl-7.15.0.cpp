static CURLcode ftp_state_loggedin(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

#ifdef HAVE_KRB4
  if(conn->data->set.krb4) {
    /* We are logged in, asked to use Kerberos. Set the requested
     * protection level
     */
    if(conn->sec_complete)
      /* BLOCKING */
      Curl_sec_set_protection_level(conn);

    /* We may need to issue a KAUTH here to have access to the files
     * do it if user supplied a password
     */
    if(conn->passwd && *conn->passwd) {
      /* BLOCKING */
      result = Curl_krb_kauth(conn);
      if(result)
        return result;
    }
  }
#endif
  if(conn->ssl[FIRSTSOCKET].use) {
    /* PBSZ = PROTECTION BUFFER SIZE.

    The 'draft-murray-auth-ftp-ssl' (draft 12, page 7) says:

    Specifically, the PROT command MUST be preceded by a PBSZ
    command and a PBSZ command MUST be preceded by a successful
    security data exchange (the TLS negotiation in this case)

    ... (and on page 8):

    Thus the PBSZ command must still be issued, but must have a
    parameter of '0' to indicate that no buffering is taking place
    and the data connection should not be encapsulated.
    */
    NBFTPSENDF(conn, "PBSZ %d", 0);
    state(conn, FTP_PBSZ);
  }
  else {
    result = ftp_state_pwd(conn);
  }
  return result;
}