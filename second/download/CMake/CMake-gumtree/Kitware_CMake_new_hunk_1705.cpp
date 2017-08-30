      snprintf((char *)&temp[len], sizeof(temp) - len,
               "%c%c", IAC, SE);
      len += 2;
      swrite(conn->firstsocket, (char*)temp, len);
      printsub(data, '>', &temp[2], len-2);
      break;
  }
