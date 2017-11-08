static CURLcode ftps_setup_connection(struct connectdata * conn)
{
  struct SessionHandle *data = conn->data;

  conn->ssl[SECONDARYSOCKET].use = data->set.ftp_ssl != CURLUSESSL_CONTROL;
  return ftp_setup_connection(conn);
}