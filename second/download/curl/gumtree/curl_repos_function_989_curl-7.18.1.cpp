static void display_conn_info(struct connectdata *conn, PRFileDesc *sock)
{
  SSLChannelInfo channel;
  SSLCipherSuiteInfo suite;
  CERTCertificate *cert;
  char *subject, *issuer, *common_name;
  PRExplodedTime printableTime;
  char timeString[256];
  PRTime notBefore, notAfter;

  if(SSL_GetChannelInfo(sock, &channel, sizeof channel) ==
    SECSuccess && channel.length == sizeof channel &&
    channel.cipherSuite) {
    if(SSL_GetCipherSuiteInfo(channel.cipherSuite,
      &suite, sizeof suite) == SECSuccess) {
      infof(conn->data, "SSL connection using %s\n", suite.cipherSuiteName);
    }
  }

  infof(conn->data, "Server certificate:\n");

  cert = SSL_PeerCertificate(sock);
  subject = CERT_NameToAscii(&cert->subject);
  issuer = CERT_NameToAscii(&cert->issuer);
  common_name = CERT_GetCommonName(&cert->subject);
  infof(conn->data, "\tsubject: %s\n", subject);

  CERT_GetCertTimes(cert, &notBefore, &notAfter);
  PR_ExplodeTime(notBefore, PR_GMTParameters, &printableTime);
  PR_FormatTime(timeString, 256, "%b %d %H:%M:%S %Y GMT", &printableTime);
  infof(conn->data, "\tstart date: %s\n", timeString);
  PR_ExplodeTime(notAfter, PR_GMTParameters, &printableTime);
  PR_FormatTime(timeString, 256, "%b %d %H:%M:%S %Y GMT", &printableTime);
  infof(conn->data, "\texpire date: %s\n", timeString);
  infof(conn->data, "\tcommon name: %s\n", common_name);
  infof(conn->data, "\tissuer: %s\n", issuer);

  PR_Free(subject);
  PR_Free(issuer);
  PR_Free(common_name);

  CERT_DestroyCertificate(cert);

  return;
}