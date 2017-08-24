{
  xcharp_u domain, dup_domain;

  /* If domain is blank or unset, check challenge message for realm */
  if(!identity->Domain || !identity->DomainLength) {
    for(;;) {
      char value[DIGEST_MAX_VALUE_LENGTH];
      char content[DIGEST_MAX_CONTENT_LENGTH];

      /* Pass all additional spaces here */
      while(*chlg && ISSPACE(*chlg))
        chlg++;

      /* Extract a value=content pair */
      if(Curl_auth_digest_get_pair(chlg, value, content, &chlg)) {
        if(strcasecompare(value, "realm")) {

          /* Setup identity's domain and length */
          domain.tchar_ptr = Curl_convert_UTF8_to_tchar((char *) content);
          if(!domain.tchar_ptr)
            return CURLE_OUT_OF_MEMORY;

          dup_domain.tchar_ptr = _tcsdup(domain.tchar_ptr);
          if(!dup_domain.tchar_ptr) {
            Curl_unicodefree(domain.tchar_ptr);
            return CURLE_OUT_OF_MEMORY;
          }

          free(identity->Domain);
          identity->Domain = dup_domain.tbyte_ptr;
          identity->DomainLength = curlx_uztoul(_tcslen(dup_domain.tchar_ptr));
          dup_domain.tchar_ptr = NULL;

          Curl_unicodefree(domain.tchar_ptr);
        }
        else {
          /* Unknown specifier, ignore it! */
        }
      }
      else
        break; /* We're done here */

      /* Pass all additional spaces here */
      while(*chlg && ISSPACE(*chlg))
        chlg++;

      /* Allow the list to be comma-separated */
      if(',' == *chlg)
        chlg++;
    }
  }

  return CURLE_OK;
}