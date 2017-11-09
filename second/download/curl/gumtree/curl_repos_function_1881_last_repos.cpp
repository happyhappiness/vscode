static ber_slen_t
ldapsb_tls_write(Sockbuf_IO_Desc *sbiod, void *buf, ber_len_t len)
{
  struct connectdata *conn = sbiod->sbiod_pvt;
  ldapconninfo *li = conn->proto.generic;
  ber_slen_t ret;
  CURLcode err = CURLE_SEND_ERROR;

  ret = li->send(conn, FIRSTSOCKET, buf, len, &err);
  if(ret < 0 && err == CURLE_AGAIN) {
    SET_SOCKERRNO(EWOULDBLOCK);
  }
  return ret;
}