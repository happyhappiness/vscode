    /* Generate a cnonce */

    now = Curl_tvnow();

    snprintf(cnoncebuf, sizeof(cnoncebuf), "%06ld", now.tv_sec);

    if(Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf), &cnonce))

      d->cnonce = cnonce;

    else

      return CURLE_OUT_OF_MEMORY;

