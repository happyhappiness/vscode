    digest->nc = 1;



  if(!digest->cnonce) {

    snprintf(cnoncebuf, sizeof(cnoncebuf), "%08x%08x%08x%08x",

             Curl_rand(data), Curl_rand(data),

             Curl_rand(data), Curl_rand(data));



    result = Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf),

                                &cnonce, &cnonce_sz);
