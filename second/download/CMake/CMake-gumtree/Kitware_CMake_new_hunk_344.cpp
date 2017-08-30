  enum protection_level data_sec = conn->data_prot;

#endif



  write_len = strlen(cmd);

  if(write_len > (sizeof(s) -3))

    return CURLE_BAD_FUNCTION_ARGUMENT;



  strcpy(&s[write_len], "\r\n"); /* append a trailing CRLF */

  write_len +=2;

