static void send_negotiation(struct connectdata *conn, int cmd, int option)
{
   unsigned char buf[3];

   buf[0] = CURL_IAC;
   buf[1] = cmd;
   buf[2] = option;

   (void)swrite(conn->sock[FIRSTSOCKET], (char *)buf, 3);

   printoption(conn->data, "SENT", cmd, option);
}