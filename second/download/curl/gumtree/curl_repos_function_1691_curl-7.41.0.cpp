CURLcode Curl_verifyhost(struct connectdata * conn,
                         const char * beg, const char * end)
{
  struct SessionHandle * data = conn->data;
  curl_X509certificate cert;
  curl_asn1Element dn;
  curl_asn1Element elem;
  curl_asn1Element ext;
  curl_asn1Element name;
  int i;
  const char * p;
  const char * q;
  char * dnsname;
  int matched = -1;
  size_t addrlen = (size_t) -1;
  ssize_t len;
#ifdef ENABLE_IPV6
  struct in6_addr addr;
#else
  struct in_addr addr;
#endif

  /* Verify that connection server matches info in X509 certificate at
     `beg'..`end'. */

  if(!data->set.ssl.verifyhost)
    return CURLE_OK;

  if(!beg)
    return CURLE_PEER_FAILED_VERIFICATION;
  Curl_parseX509(&cert, beg, end);

  /* Get the server IP address. */
#ifdef ENABLE_IPV6
  if(conn->bits.ipv6_ip && Curl_inet_pton(AF_INET6, conn->host.name, &addr))
    addrlen = sizeof(struct in6_addr);
  else
#endif
  if(Curl_inet_pton(AF_INET, conn->host.name, &addr))
    addrlen = sizeof(struct in_addr);

  /* Process extensions. */
  for(p = cert.extensions.beg; p < cert.extensions.end && matched != 1;) {
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
        switch (name.tag) {
        case 2: /* DNS name. */
          i = 0;
          len = utf8asn1str(&dnsname, CURL_ASN1_IA5_STRING,
                            name.beg, name.end);
          if(len > 0)
            if(strlen(dnsname) == (size_t) len)
              i = Curl_cert_hostcheck((const char *) dnsname, conn->host.name);
          if(dnsname)
            free(dnsname);
          if(!i)
            return CURLE_PEER_FAILED_VERIFICATION;
          matched = i;
          break;

        case 7: /* IP address. */
          matched = (size_t) (name.end - q) == addrlen &&
                    !memcmp(&addr, q, addrlen);
          break;
        }
      }
    }
  }

  switch (matched) {
  case 1:
    /* an alternative name matched the server hostname */
    infof(data, "\t subjectAltName: %s matched\n", conn->host.dispname);
    return CURLE_OK;
  case 0:
    /* an alternative name field existed, but didn't match and then
       we MUST fail */
    infof(data, "\t subjectAltName does not match %s\n", conn->host.dispname);
    return CURLE_PEER_FAILED_VERIFICATION;
  }

  /* Process subject. */
  name.header = NULL;
  name.beg = name.end = "";
  q = cert.subject.beg;
  /* we have to look to the last occurrence of a commonName in the
     distinguished one to get the most significant one. */
  while(q < cert.subject.end) {
    q = Curl_getASN1Element(&dn, q, cert.subject.end);
    for(p = dn.beg; p < dn.end;) {
      p = Curl_getASN1Element(&elem, p, dn.end);
      /* We have a DN's AttributeTypeAndValue: check it in case it's a CN. */
      elem.beg = checkOID(elem.beg, elem.end, cnOID);
      if(elem.beg)
        name = elem;    /* Latch CN. */
    }
  }

  /* Check the CN if found. */
  if(!Curl_getASN1Element(&elem, name.beg, name.end))
    failf(data, "SSL: unable to obtain common name from peer certificate");
  else {
    len = utf8asn1str(&dnsname, elem.tag, elem.beg, elem.end);
    if(len < 0) {
      free(dnsname);
      return CURLE_OUT_OF_MEMORY;
    }
    if(strlen(dnsname) != (size_t) len)         /* Nul byte in string ? */
      failf(data, "SSL: illegal cert name field");
    else if(Curl_cert_hostcheck((const char *) dnsname, conn->host.name)) {
      infof(data, "\t common name: %s (matched)\n", dnsname);
      free(dnsname);
      return CURLE_OK;
    }
    else
      failf(data, "SSL: certificate subject name '%s' does not match "
            "target host name '%s'", dnsname, conn->host.dispname);
    free(dnsname);
  }

  return CURLE_PEER_FAILED_VERIFICATION;
}