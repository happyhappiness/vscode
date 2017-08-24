r(p2 = rdn.beg; p2 < rdn.end;) {
      p2 = Curl_getASN1Element(&atv, p2, rdn.end);
      p3 = Curl_getASN1Element(&oid, atv.beg, atv.end);
      Curl_getASN1Element(&value, p3, atv.end);
      str = Curl_ASN1tostr(&oid, 0);
      if(!str)
        return -1;

      /* Encode delimiter.
         If attribute has a short uppercase name, delimiter is ", ". */
      if(l) {
        for(p3 = str; isupper(*p3); p3++)
          ;
        for(p3 = (*p3 || p3 - str > 2)? "/": ", "; *p3; p3++) {
          if(l < n)
            buf[l] = *p3;
          l++;
        }
      }

      /* Encode attribute name. */
      for(p3 = str; *p3; p3++) {
        if(l < n)
          buf[l] = *p3;
        l++;
      }
      free((char *) str);

      /* Generate equal sign. */
      if(l < n)
        buf[l] = '=';
      l++;

      /* Generate value. */
      str = Curl_ASN1tostr(&value, 0);
      if(!str)
        return -1;
      for(p3 = str; *p3; p3++) {
        if(l < n)
          buf[l] = *p3;
        l++;
      }
      free((char *) str);
    }