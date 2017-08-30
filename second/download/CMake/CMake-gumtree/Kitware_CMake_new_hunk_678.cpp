    }
#endif

    if(strcmp("Host:", ptr)) {
      conn->allocptr.host = aprintf("%s\r\n", ptr);
      if(!conn->allocptr.host)
        return CURLE_OUT_OF_MEMORY;
    }
    else
      /* when clearing the header */
      conn->allocptr.host = NULL;
  }
  else {
    /* When building Host: headers, we must put the host name within
