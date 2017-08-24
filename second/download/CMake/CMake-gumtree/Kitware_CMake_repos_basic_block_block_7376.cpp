{
    p = Curl_getASN1Element(&elem, pk.beg, pk.end);
    /* Compute key length. */
    for(q = elem.beg; !*q && q < elem.end; q++)
      ;
    len = (unsigned long)((elem.end - q) * 8);
    if(len)
      for(i = *(unsigned char *) q; !(i & 0x80); i <<= 1)
        len--;
    if(len > 32)
      elem.beg = q;     /* Strip leading zero bytes. */
    if(!certnum)
      infof(data, "   RSA Public Key (%lu bits)\n", len);
    if(data->set.ssl.certinfo) {
      q = curl_maprintf("%lu", len);
      if(q) {
        Curl_ssl_push_certinfo(data, certnum, "RSA Public Key", q);
        free((char *) q);
      }
    }
    /* Generate coefficients. */
    do_pubkey_field(data, certnum, "rsa(n)", &elem);
    Curl_getASN1Element(&elem, p, pk.end);
    do_pubkey_field(data, certnum, "rsa(e)", &elem);
  }