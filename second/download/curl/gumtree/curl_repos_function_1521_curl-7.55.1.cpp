static CURLcode smb_send_negotiate(struct connectdata *conn)
{
  const char *msg = "\x00\x0c\x00\x02NT LM 0.12";

  return smb_send_message(conn, SMB_COM_NEGOTIATE, msg, 15);
}