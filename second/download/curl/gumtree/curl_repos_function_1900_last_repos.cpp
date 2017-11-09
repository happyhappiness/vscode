static CURLcode ftp_state_use_pasv(struct connectdata *conn)
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  CURLcode result = CURLE_OK;
  /*
    Here's the excecutive summary on what to do:

    PASV is RFC959, expect:
    227 Entering Passive Mode (a1,a2,a3,a4,p1,p2)

    LPSV is RFC1639, expect:
    228 Entering Long Passive Mode (4,4,a1,a2,a3,a4,2,p1,p2)

    EPSV is RFC2428, expect:
    229 Entering Extended Passive Mode (|||port|)

  */

  static const char mode[][5] = { "EPSV", "PASV" };
  int modeoff;

#ifdef PF_INET6
  if(!conn->bits.ftp_use_epsv && conn->bits.ipv6)
    /* EPSV is disabled but we are connected to a IPv6 host, so we ignore the
       request and enable EPSV again! */
    conn->bits.ftp_use_epsv = TRUE;
#endif

  modeoff = conn->bits.ftp_use_epsv?0:1;

  PPSENDF(&ftpc->pp, "%s", mode[modeoff]);

  ftpc->count1 = modeoff;
  state(conn, FTP_PASV);
  infof(conn->data, "Connect data stream passively\n");

  return result;
}