static void do_pubkey(struct Curl_easy *data, int certnum,
                      const char *algo, curl_asn1Element *param,
                      curl_asn1Element *pubkey)
{
  curl_asn1Element elem;
  curl_asn1Element pk;
  const char *p;
  const char *q;
  unsigned long len;
  unsigned int i;

  /* Generate all information records for the public key. */

  /* Get the public key (single element). */
  Curl_getASN1Element(&pk, pubkey->beg + 1, pubkey->end);

  if(strcasecompare(algo, "rsaEncryption")) {
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
  else if(strcasecompare(algo, "dsa")) {
    p = Curl_getASN1Element(&elem, param->beg, param->end);
    do_pubkey_field(data, certnum, "dsa(p)", &elem);
    p = Curl_getASN1Element(&elem, p, param->end);
    do_pubkey_field(data, certnum, "dsa(q)", &elem);
    Curl_getASN1Element(&elem, p, param->end);
    do_pubkey_field(data, certnum, "dsa(g)", &elem);
    do_pubkey_field(data, certnum, "dsa(pub_key)", &pk);
  }
  else if(strcasecompare(algo, "dhpublicnumber")) {
    p = Curl_getASN1Element(&elem, param->beg, param->end);
    do_pubkey_field(data, certnum, "dh(p)", &elem);
    Curl_getASN1Element(&elem, param->beg, param->end);
    do_pubkey_field(data, certnum, "dh(g)", &elem);
    do_pubkey_field(data, certnum, "dh(pub_key)", &pk);
  }
#if 0 /* Patent-encumbered. */
  else if(strcasecompare(algo, "ecPublicKey")) {
    /* Left TODO. */
  }
#endif
}