static void send_negotiation(struct connectdata *conn, int cmd, int option)
{
   unsigned char buf[3];
   ssize_t bytes_written;
   int err;
   struct SessionHandle *data = conn->data;

   buf[0] = CURL_IAC;
   buf[1] = (unsigned char)cmd;
   buf[2] = (unsigned char)option;

   bytes_written = swrite(conn->sock[FIRSTSOCKET], buf, 3);
   if(bytes_written < 0) {
     err = SOCKERRNO;
     failf(data,"Sending data failed (%d)",err);
   }

   printoption(conn->data, "SENT", cmd, option);
}