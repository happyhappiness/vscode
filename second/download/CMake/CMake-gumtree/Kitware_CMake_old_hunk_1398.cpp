         (40)    Target Information  (optional) security buffer(*)
         32 (48) start of data block
      */

      size_t size = Curl_base64_decode(header, (char *)buffer);

      ntlm->state = NTLMSTATE_TYPE2; /* we got a type-2 */

      if(size >= 48)
        /* the nonce of interest is index [24 .. 31], 8 bytes */
        memcpy(ntlm->nonce, &buffer[24], 8);

      /* at index decimal 20, there's a 32bit NTLM flag field */

    }
    else {
      if(ntlm->state >= NTLMSTATE_TYPE1)
