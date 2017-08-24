{
    Curl_safefree(connssl->decdata_buffer);
    connssl->decdata_length = 0;
    connssl->decdata_offset = 0;
  }