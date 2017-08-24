{
    len = utf8asn1str(&dnsname, elem.tag, elem.beg, elem.end);
    if(len < 0) {
      free(dnsname);
      return CURLE_OUT_OF_MEMORY;
    }
    if(strlen(dnsname) != (size_t) len)         /* Nul byte in string ? */
      failf(data, "SSL: illegal cert name field");
    else if(Curl_cert_hostcheck((const char *) dnsname, hostname)) {
      infof(data, "\t common name: %s (matched)\n", dnsname);
      free(dnsname);
      return CURLE_OK;
    }
    else
      failf(data, "SSL: certificate subject name '%s' does not match "
            "target host name '%s'", dnsname, dispname);
    free(dnsname);
  }