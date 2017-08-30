{
    unsigned int rnd[4];
    result = Curl_rand(data, &rnd[0], 4);
    if(result)
      return result;
    snprintf(cnoncebuf, sizeof(cnoncebuf), "%08x%08x%08x%08x",
             rnd[0], rnd[1], rnd[2], rnd[3]);

    result = Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf),
                                &cnonce, &cnonce_sz);
    if(result)
      return result;

    digest->cnonce = cnonce;
  }