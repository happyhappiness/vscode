  struct SessionHandle *data = conn->data;
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;

  printsub(data, '<', (unsigned char *)tn->subbuffer, (int)SB_LEN(tn)+2);
  switch (subchar = (unsigned char)SB_GET(tn)) {
    case TELOPT_TTYPE:
      len = (int)strlen(tn->subopt_ttype) + 4 + 2;
      snprintf((char *)temp, sizeof(temp),
               "%c%c%c%c%s%c%c", IAC, SB, TELOPT_TTYPE,
               TELQUAL_IS, tn->subopt_ttype, IAC, SE);
      swrite(conn->firstsocket, (char*)temp, len);
      printsub(data, '>', &temp[2], len-2);
      break;
    case TELOPT_XDISPLOC:
      len = (int)strlen(tn->subopt_xdisploc) + 4 + 2;
      snprintf((char *)temp, sizeof(temp),
               "%c%c%c%c%s%c%c", IAC, SB, TELOPT_XDISPLOC,
               TELQUAL_IS, tn->subopt_xdisploc, IAC, SE);
