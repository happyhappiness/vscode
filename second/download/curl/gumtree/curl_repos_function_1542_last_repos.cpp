static void smb_pop_message(struct connectdata *conn)
{
  struct smb_conn *smbc = &conn->proto.smbc;

  smbc->got = 0;
}