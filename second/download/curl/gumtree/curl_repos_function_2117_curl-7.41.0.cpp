static CURLcode get_cert_chain(struct connectdata *conn,
                               struct ssl_connect_data *connssl)

{
  CURLcode result;
  STACK_OF(X509) *sk;
  int i;
  char *bufp;
  struct SessionHandle *data = conn->data;
  int numcerts;

  bufp = malloc(CERTBUFFERSIZE);
  if(!bufp)
    return CURLE_OUT_OF_MEMORY;

  sk = SSL_get_peer_cert_chain(connssl->handle);
  if(!sk) {
    free(bufp);
    return CURLE_OUT_OF_MEMORY;
  }

  numcerts = sk_X509_num(sk);

  result = Curl_ssl_init_certinfo(data, numcerts);
  if(result) {
    free(bufp);
    return result;
  }

  infof(data, "--- Certificate chain\n");
  for(i=0; i<numcerts; i++) {
    long value;
    ASN1_INTEGER *num;
    ASN1_TIME *certdate;

    /* get the certs in "importance order" */
#if 0
    X509 *x = sk_X509_value(sk, numcerts - i - 1);
#else
    X509 *x = sk_X509_value(sk, i);
#endif

    X509_CINF *cinf;
    EVP_PKEY *pubkey=NULL;
    int j;
    char *ptr;

    (void)x509_name_oneline(X509_get_subject_name(x), bufp, CERTBUFFERSIZE);
    infof(data, "%2d Subject: %s\n", i, bufp);
    Curl_ssl_push_certinfo(data, i, "Subject", bufp);

    (void)x509_name_oneline(X509_get_issuer_name(x), bufp, CERTBUFFERSIZE);
    infof(data, "   Issuer: %s\n", bufp);
    Curl_ssl_push_certinfo(data, i, "Issuer", bufp);

    value = X509_get_version(x);
    infof(data, "   Version: %lu (0x%lx)\n", value+1, value);
    snprintf(bufp, CERTBUFFERSIZE, "%lx", value);
    Curl_ssl_push_certinfo(data, i, "Version", bufp); /* hex */

    num=X509_get_serialNumber(x);
    if(num->length <= 4) {
      value = ASN1_INTEGER_get(num);
      infof(data,"   Serial Number: %ld (0x%lx)\n", value, value);
      snprintf(bufp, CERTBUFFERSIZE, "%lx", value);
    }
    else {
      int left = CERTBUFFERSIZE;

      ptr = bufp;
      *ptr++ = 0;
      if(num->type == V_ASN1_NEG_INTEGER)
        *ptr++='-';

      for(j=0; (j<num->length) && (left>=4); j++) {
        /* TODO: length restrictions */
        snprintf(ptr, 3, "%02x%c",num->data[j],
                 ((j+1 == num->length)?'\n':':'));
        ptr += 3;
        left-=4;
      }
      if(num->length)
        infof(data,"   Serial Number: %s\n", bufp);
      else
        bufp[0]=0;
    }
    if(bufp[0])
      Curl_ssl_push_certinfo(data, i, "Serial Number", bufp); /* hex */

    cinf = x->cert_info;

    j = asn1_object_dump(cinf->signature->algorithm, bufp, CERTBUFFERSIZE);
    if(!j) {
      infof(data, "   Signature Algorithm: %s\n", bufp);
      Curl_ssl_push_certinfo(data, i, "Signature Algorithm", bufp);
    }

    certdate = X509_get_notBefore(x);
    asn1_output(certdate, bufp, CERTBUFFERSIZE);
    infof(data, "   Start date: %s\n", bufp);
    Curl_ssl_push_certinfo(data, i, "Start date", bufp);

    certdate = X509_get_notAfter(x);
    asn1_output(certdate, bufp, CERTBUFFERSIZE);
    infof(data, "   Expire date: %s\n", bufp);
    Curl_ssl_push_certinfo(data, i, "Expire date", bufp);

    j = asn1_object_dump(cinf->key->algor->algorithm, bufp, CERTBUFFERSIZE);
    if(!j) {
      infof(data, "   Public Key Algorithm: %s\n", bufp);
      Curl_ssl_push_certinfo(data, i, "Public Key Algorithm", bufp);
    }

    pubkey = X509_get_pubkey(x);
    if(!pubkey)
      infof(data, "   Unable to load public key\n");
    else {
      switch(pubkey->type) {
      case EVP_PKEY_RSA:
        infof(data,  "   RSA Public Key (%d bits)\n",
              BN_num_bits(pubkey->pkey.rsa->n));
        snprintf(bufp, CERTBUFFERSIZE, "%d", BN_num_bits(pubkey->pkey.rsa->n));
        Curl_ssl_push_certinfo(data, i, "RSA Public Key", bufp);

        print_pubkey_BN(rsa, n, i);
        print_pubkey_BN(rsa, e, i);
        print_pubkey_BN(rsa, d, i);
        print_pubkey_BN(rsa, p, i);
        print_pubkey_BN(rsa, q, i);
        print_pubkey_BN(rsa, dmp1, i);
        print_pubkey_BN(rsa, dmq1, i);
        print_pubkey_BN(rsa, iqmp, i);
        break;
      case EVP_PKEY_DSA:
        print_pubkey_BN(dsa, p, i);
        print_pubkey_BN(dsa, q, i);
        print_pubkey_BN(dsa, g, i);
        print_pubkey_BN(dsa, priv_key, i);
        print_pubkey_BN(dsa, pub_key, i);
        break;
      case EVP_PKEY_DH:
        print_pubkey_BN(dh, p, i);
        print_pubkey_BN(dh, g, i);
        print_pubkey_BN(dh, priv_key, i);
        print_pubkey_BN(dh, pub_key, i);
        break;
#if 0
      case EVP_PKEY_EC: /* symbol not present in OpenSSL 0.9.6 */
        /* left TODO */
        break;
#endif
      }
      EVP_PKEY_free(pubkey);
    }

    X509V3_ext(data, i, cinf->extensions);

    X509_signature(data, i, x->signature);

    dumpcert(data, x, i);
  }

  free(bufp);

  return CURLE_OK;
}