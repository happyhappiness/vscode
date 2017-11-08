static SECStatus HandshakeCallback(PRFileDesc *sock, void *arg)
{
  (void)sock;
  (void)arg;
  return SECSuccess;
}