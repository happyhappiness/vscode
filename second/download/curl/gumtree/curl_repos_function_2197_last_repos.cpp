bool Curl_sasl_can_authenticate(struct SASL *sasl, struct connectdata *conn)
{
  /* Have credentials been provided? */
  if(conn->bits.user_passwd)
    return TRUE;

  /* EXTERNAL can authenticate without a user name and/or password */
  if(sasl->authmechs & sasl->prefmech & SASL_MECH_EXTERNAL)
    return TRUE;

  return FALSE;
}