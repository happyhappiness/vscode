static int
ldapsb_tls_ctrl(Sockbuf_IO_Desc *sbiod, int opt, void *arg)
{
  (void)arg;
  if(opt == LBER_SB_OPT_DATA_READY) {
    struct connectdata *conn = sbiod->sbiod_pvt;
    return Curl_ssl_data_pending(conn, FIRSTSOCKET);
  }
  return 0;
}