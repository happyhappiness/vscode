    return CURLE_BAD_CONTENT_ENCODING;



  /* Generate 16 bytes of random data */

  entropy[0] = Curl_rand(data);

  entropy[1] = Curl_rand(data);

  entropy[2] = Curl_rand(data);

  entropy[3] = Curl_rand(data);



  /* Convert the random data into a 32 byte hex string */

  snprintf(cnonce, sizeof(cnonce), "%08x%08x%08x%08x",

