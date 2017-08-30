    return CURLE_BAD_CONTENT_ENCODING;



  /* Generate 16 bytes of random data */

  result = Curl_rand(data, &entropy[0], 4);

  if(result)

    return result;



  /* Convert the random data into a 32 byte hex string */

  snprintf(cnonce, sizeof(cnonce), "%08x%08x%08x%08x",

