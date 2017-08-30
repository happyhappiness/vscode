    digest->nc = 1;

  if(!digest->cnonce) {
    result = Curl_rand_hex(data, (unsigned char *)cnoncebuf,
                           sizeof(cnoncebuf));
    if(result)
      return result;

    result = Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf),
                                &cnonce, &cnonce_sz);