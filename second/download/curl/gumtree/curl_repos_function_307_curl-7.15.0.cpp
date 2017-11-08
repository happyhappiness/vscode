static CURLcode verifyhost(struct connectdata *conn,
                           X509 *server_cert)
{
  bool matched = FALSE; /* no alternative match yet */
  int target = GEN_DNS; /* target type, GEN_DNS or GEN_IPADD */
  int addrlen = 0;
  struct SessionHandle *data = conn->data;
  STACK_OF(GENERAL_NAME) *altnames;
#ifdef ENABLE_IPV6
  struct in6_addr addr;
#else
  struct in_addr addr;
#endif
  CURLcode res = CURLE_OK;

#ifdef ENABLE_IPV6
  if(conn->bits.ipv6_ip &&
     Curl_inet_pton(AF_INET6, conn->host.name, &addr)) {
    target = GEN_IPADD;
    addrlen = sizeof(struct in6_addr);
  }
  else
#endif
    if(Curl_inet_pton(AF_INET, conn->host.name, &addr)) {
      target = GEN_IPADD;
      addrlen = sizeof(struct in_addr);
    }

  /* get a "list" of alternative names */
  altnames = X509_get_ext_d2i(server_cert, NID_subject_alt_name, NULL, NULL);

  if(altnames) {
    int numalts;
    int i;

    /* get amount of alternatives, RFC2459 claims there MUST be at least
       one, but we don't depend on it... */
    numalts = sk_GENERAL_NAME_num(altnames);

    /* loop through all alternatives while none has matched */
    for (i=0; (i<numalts) && !matched; i++) {
      /* get a handle to alternative name number i */
      const GENERAL_NAME *check = sk_GENERAL_NAME_value(altnames, i);

      /* only check alternatives of the same type the target is */
      if(check->type == target) {
        /* get data and length */
        const char *altptr = (char *)ASN1_STRING_data(check->d.ia5);
        int altlen;

        switch(target) {
        case GEN_DNS: /* name/pattern comparison */
          /* The OpenSSL man page explicitly says: "In general it cannot be
             assumed that the data returned by ASN1_STRING_data() is null
             terminated or does not contain embedded nulls." But also that
             "The actual format of the data will depend on the actual string
             type itself: for example for and IA5String the data will be ASCII"

             Gisle researched the OpenSSL sources:
             "I checked the 0.9.6 and 0.9.8 sources before my patch and
             it always 0-terminates an IA5String."
          */
          if (cert_hostcheck(altptr, conn->host.name))
            matched = TRUE;
          break;

        case GEN_IPADD: /* IP address comparison */
          /* compare alternative IP address if the data chunk is the same size
             our server IP address is */
          altlen = ASN1_STRING_length(check->d.ia5);
          if((altlen == addrlen) && !memcmp(altptr, &addr, altlen))
            matched = TRUE;
          break;
        }
      }
    }
    GENERAL_NAMES_free(altnames);
  }

  if(matched)
    /* an alternative name matched the server hostname */
    infof(data, "\t subjectAltName: %s matched\n", conn->host.dispname);
  else {
    /* we have to look to the last occurence of a commonName in the
       distinguished one to get the most significant one. */
    int j,i=-1 ;

/* The following is done because of a bug in 0.9.6b */

    unsigned char *nulstr = (unsigned char *)"";
    unsigned char *peer_CN = nulstr;

    X509_NAME *name = X509_get_subject_name(server_cert) ;
    if (name)
      while ((j=X509_NAME_get_index_by_NID(name,NID_commonName,i))>=0)
        i=j;

    /* we have the name entry and we will now convert this to a string
       that we can use for comparison. Doing this we support BMPstring,
       UTF8 etc. */

    if (i>=0) {
      ASN1_STRING *tmp = X509_NAME_ENTRY_get_data(X509_NAME_get_entry(name,i));

      /* In OpenSSL 0.9.7d and earlier, ASN1_STRING_to_UTF8 fails if the input
         is already UTF-8 encoded. We check for this case and copy the raw
         string manually to avoid the problem. This code can be made
         conditional in the future when OpenSSL has been fixed. Work-around
         brought by Alexis S. L. Carvalho. */
      if (tmp && ASN1_STRING_type(tmp) == V_ASN1_UTF8STRING) {
        j = ASN1_STRING_length(tmp);
        if (j >= 0) {
          peer_CN = OPENSSL_malloc(j+1);
          if (peer_CN) {
            memcpy(peer_CN, ASN1_STRING_data(tmp), j);
            peer_CN[j] = '\0';
          }
        }
      }
      else /* not a UTF8 name */
        j = ASN1_STRING_to_UTF8(&peer_CN, tmp);
    }

    if (peer_CN == nulstr)
       peer_CN = NULL;

    if (!peer_CN) {
      if(data->set.ssl.verifyhost > 1) {
        failf(data,
              "SSL: unable to obtain common name from peer certificate");
        return CURLE_SSL_PEER_CERTIFICATE;
      }
      else {
        /* Consider verifyhost == 1 as an "OK" for a missing CN field, but we
           output a note about the situation */
        infof(data, "\t common name: WARNING couldn't obtain\n");
      }
    }
    else if(!cert_hostcheck((const char *)peer_CN, conn->host.name)) {
      if(data->set.ssl.verifyhost > 1) {
        failf(data, "SSL: certificate subject name '%s' does not match "
              "target host name '%s'", peer_CN, conn->host.dispname);
        res = CURLE_SSL_PEER_CERTIFICATE;
      }
      else
        infof(data, "\t common name: %s (does not match '%s')\n",
              peer_CN, conn->host.dispname);
    }
    else {
      infof(data, "\t common name: %s (matched)\n", peer_CN);
    }
    if(peer_CN)
      OPENSSL_free(peer_CN);
  }
  return res;
}