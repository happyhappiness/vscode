static void suboption(struct connectdata *conn)
{
  struct curl_slist *v;
  unsigned char subchar;
  unsigned char temp[2048];
  int len;
  int tmplen;
  char varname[128];
  char varval[128];
  struct SessionHandle *data = conn->data;
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
      snprintf((char *)temp, sizeof(temp),
               "%c%c%c%c", IAC, SB, TELOPT_NEW_ENVIRON, TELQUAL_IS);
      len = 4;

      for(v = tn->telnet_vars;v;v = v->next) {
        tmplen = (strlen(v->data) + 1);
        /* Add the variable only if it fits */
        if(len + tmplen < (int)sizeof(temp)-6) {
          sscanf(v->data, "%127[^,],%s", varname, varval);
          snprintf((char *)&temp[len], sizeof(temp) - len,
                   "%c%s%c%s", NEW_ENV_VAR, varname,
                   NEW_ENV_VALUE, varval);
          len += tmplen;
        }
      }
      snprintf((char *)&temp[len], sizeof(temp) - len,
               "%c%c", IAC, SE);
      len += 2;
      swrite(conn->firstsocket, temp, len);
      printsub(data, '>', &temp[2], len-2);
      break;
  }
  return;
}