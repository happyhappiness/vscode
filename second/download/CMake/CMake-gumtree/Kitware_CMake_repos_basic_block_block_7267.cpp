{
#ifdef curlssl_sha256sum
    /* compute sha256sum of public key */
    sha256sumdigest = malloc(SHA256_DIGEST_LENGTH);
    if(!sha256sumdigest)
      return CURLE_OUT_OF_MEMORY;
    curlssl_sha256sum(pubkey, pubkeylen,
                      sha256sumdigest, SHA256_DIGEST_LENGTH);
    encode = Curl_base64_encode(data, (char *)sha256sumdigest,
                                SHA256_DIGEST_LENGTH, &encoded, &encodedlen);
    Curl_safefree(sha256sumdigest);

    if(encode)
      return encode;

    infof(data, "\t public key hash: sha256//%s\n", encoded);

    /* it starts with sha256//, copy so we can modify it */
    pinkeylen = strlen(pinnedpubkey) + 1;
    pinkeycopy = malloc(pinkeylen);
    if(!pinkeycopy) {
      Curl_safefree(encoded);
      return CURLE_OUT_OF_MEMORY;
    }
    memcpy(pinkeycopy, pinnedpubkey, pinkeylen);
    /* point begin_pos to the copy, and start extracting keys */
    begin_pos = pinkeycopy;
    do {
      end_pos = strstr(begin_pos, ";sha256//");
      /*
       * if there is an end_pos, null terminate,
       * otherwise it'll go to the end of the original string
       */
      if(end_pos)
        end_pos[0] = '\0';

      /* compare base64 sha256 digests, 8 is the length of "sha256//" */
      if(encodedlen == strlen(begin_pos + 8) &&
         !memcmp(encoded, begin_pos + 8, encodedlen)) {
        result = CURLE_OK;
        break;
      }

      /*
       * change back the null-terminator we changed earlier,
       * and look for next begin
       */
      if(end_pos) {
        end_pos[0] = ';';
        begin_pos = strstr(end_pos, "sha256//");
      }
    } while(end_pos && begin_pos);
    Curl_safefree(encoded);
    Curl_safefree(pinkeycopy);
#else
    /* without sha256 support, this cannot match */
    (void)data;
#endif
    return result;
  }