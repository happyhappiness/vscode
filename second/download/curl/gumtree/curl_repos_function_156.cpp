static void send_negotiation(struct UrlData *data, int cmd, int option)
{
   unsigned char buf[3];

   buf[0] = IAC;
   buf[1] = cmd;
   buf[2] = option;
   
   swrite(data->firstsocket, buf, 3);
   
   printoption(data, "SENT", cmd, option);
}