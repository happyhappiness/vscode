{
    p = Curl_getASN1Element(&ext, p, cert.extensions.end);
    /* Check if extension is a subjectAlternativeName. */
    ext.beg = checkOID(ext.beg, ext.end, sanOID);
    if(ext.beg) {
      ext.beg = Curl_getASN1Element(&elem, ext.beg, ext.end);
      /* Skip critical if present. */
      if(elem.tag == CURL_ASN1_BOOLEAN)
        ext.beg = Curl_getASN1Element(&elem, ext.beg, ext.end);
      /* Parse the octet string contents: is a single sequence. */
      Curl_getASN1Element(&elem, elem.beg, elem.end);
      /* Check all GeneralNames. */
      for(q = elem.beg; matched != 1 && q < elem.end;) {
        q = Curl_getASN1Element(&name, q, elem.end);
        switch(name.tag) {
        case 2: /* DNS name. */
          len = utf8asn1str(&dnsname, CURL_ASN1_IA5_STRING,
                            name.beg, name.end);
          if(len > 0 && (size_t)len == strlen(dnsname))
            matched = Curl_cert_hostcheck(dnsname, hostname);
          else
            matched = 0;
          free(dnsname);
          break;

        case 7: /* IP address. */
          matched = (size_t) (name.end - q) == addrlen &&
                    !memcmp(&addr, q, addrlen);
          break;
        }
      }
    }
  }