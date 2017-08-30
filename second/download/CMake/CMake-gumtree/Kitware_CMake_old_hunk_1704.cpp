  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;



  printsub(data, '<', (unsigned char *)tn->subbuffer, SB_LEN(tn)+2);

  switch (subchar = SB_GET(tn)) {

    case TELOPT_TTYPE:

      len = strlen(tn->subopt_ttype) + 4 + 2;

      snprintf((char *)temp, sizeof(temp),

               "%c%c%c%c%s%c%c", IAC, SB, TELOPT_TTYPE,

               TELQUAL_IS, tn->subopt_ttype, IAC, SE);

      swrite(conn->firstsocket, temp, len);

      printsub(data, '>', &temp[2], len-2);

      break;

    case TELOPT_XDISPLOC:

      len = strlen(tn->subopt_xdisploc) + 4 + 2;

      snprintf((char *)temp, sizeof(temp),

               "%c%c%c%c%s%c%c", IAC, SB, TELOPT_XDISPLOC,

               TELQUAL_IS, tn->subopt_xdisploc, IAC, SE);

      swrite(conn->firstsocket, temp, len);

      printsub(data, '>', &temp[2], len-2);

      break;

    case TELOPT_NEW_ENVIRON:

