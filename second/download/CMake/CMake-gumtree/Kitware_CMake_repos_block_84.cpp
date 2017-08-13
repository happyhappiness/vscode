{
    Curl_safefree(conn->allocptr.uagent);
    conn->allocptr.uagent =
      aprintf("User-Agent: %s\r\n", data->set.str[STRING_USERAGENT]);
    if(!conn->allocptr.uagent)
      return CURLE_OUT_OF_MEMORY;
  }