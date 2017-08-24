{
    free(trailer);
    Curl_unicodefree(user_name);

    return CURLE_OUT_OF_MEMORY;
  }