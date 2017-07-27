conn->allocptr.te = cptr? aprintf("%s, TE\r\n" TE_HEADER, cptr):
      strdup("Connection: TE\r\n" TE_HEADER);