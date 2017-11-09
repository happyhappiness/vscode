static CURLcode get_cert_chain(struct connectdata *conn,
                               struct ssl_connect_data *connssl)

{
  CURLcode result;
  STACK_OF(X509) *sk;
  int i;
  struct Curl_easy *data = conn->data;
  int numcerts;
  BIO *mem;

  sk = SSL_get_peer_cert_chain(BACKEND->handle);
  if(!sk) {
    return CURLE_OUT_OF_MEMORY;
  }

  numcerts = sk_X509_num(sk);

  result = Curl_ssl_init_certinfo(data, numcerts);
  if(result) {
    return result;
  }

  mem = BIO_new(BIO_s_mem());

  for(i = 0; i < numcerts; i++) {
    ASN1_INTEGER *num;
    X509 *x = sk_X509_value(sk, i);
    EVP_PKEY *pubkey = NULL;
    int j;
    char *ptr;
    const ASN1_BIT_STRING *psig = NULL;

    X509_NAME_print_ex(mem, X509_get_subject_name(x), 0, XN_FLAG_ONELINE);
    push_certinfo("Subject", i);

    X509_NAME_print_ex(mem, X509_get_issuer_name(x), 0, XN_FLAG_ONELINE);
    push_certinfo("Issuer", i);

    BIO_printf(mem, "%lx", X509_get_version(x));
    push_certinfo("Version", i);

    num = X509_get_serialNumber(x);
    if(num->type == V_ASN1_NEG_INTEGER)
      BIO_puts(mem, "-");
    for(j = 0; j < num->length; j++)
      BIO_printf(mem, "%02x", num->data[j]);
    push_certinfo("Serial Number", i);

#if defined(HAVE_X509_GET0_SIGNATURE) && defined(HAVE_X509_GET0_EXTENSIONS)
    {
      const X509_ALGOR *palg = NULL;
      ASN1_STRING *a = ASN1_STRING_new();
      if(a) {
        X509_get0_signature(&psig, &palg, x);
        X509_signature_print(mem, palg, a);
        ASN1_STRING_free(a);

        if(palg) {
          i2a_ASN1_OBJECT(mem, palg->algorithm);
          push_certinfo("Public Key Algorithm", i);
        }
      }
      X509V3_ext(data, i, X509_get0_extensions(x));
    }
#else
    {
      /* before OpenSSL 1.0.2 */
      X509_CINF *cinf = x->cert_info;

      i2a_ASN1_OBJECT(mem, cinf->signature->algorithm);
      push_certinfo("Signature Algorithm", i);

      i2a_ASN1_OBJECT(mem, cinf->key->algor->algorithm);
      push_certinfo("Public Key Algorithm", i);

      X509V3_ext(data, i, cinf->extensions);

      psig = x->signature;
    }
#endif

    ASN1_TIME_print(mem, X509_get0_notBefore(x));
    push_certinfo("Start date", i);

    ASN1_TIME_print(mem, X509_get0_notAfter(x));
    push_certinfo("Expire date", i);

    pubkey = X509_get_pubkey(x);
    if(!pubkey)
      infof(data, "   Unable to load public key\n");
    else {
      int pktype;
#ifdef HAVE_OPAQUE_EVP_PKEY
      pktype = EVP_PKEY_id(pubkey);
#else
      pktype = pubkey->type;
#endif
      switch(pktype) {
      case EVP_PKEY_RSA:
      {
        RSA *rsa;
#ifdef HAVE_OPAQUE_EVP_PKEY
        rsa = EVP_PKEY_get0_RSA(pubkey);
#else
        rsa = pubkey->pkey.rsa;
#endif

#ifdef HAVE_OPAQUE_RSA_DSA_DH
        {
          const BIGNUM *n;
          const BIGNUM *e;

          RSA_get0_key(rsa, &n, &e, NULL);
          BN_print(mem, n);
          push_certinfo("RSA Public Key", i);
          print_pubkey_BN(rsa, n, i);
          print_pubkey_BN(rsa, e, i);
        }
#else
        BIO_printf(mem, "%d", BN_num_bits(rsa->n));
        push_certinfo("RSA Public Key", i);
        print_pubkey_BN(rsa, n, i);
        print_pubkey_BN(rsa, e, i);
#endif

        break;
      }
      case EVP_PKEY_DSA:
      {
#ifndef OPENSSL_NO_DSA
        DSA *dsa;
#ifdef HAVE_OPAQUE_EVP_PKEY
        dsa = EVP_PKEY_get0_DSA(pubkey);
#else
        dsa = pubkey->pkey.dsa;
#endif
#ifdef HAVE_OPAQUE_RSA_DSA_DH
        {
          const BIGNUM *p;
          const BIGNUM *q;
          const BIGNUM *g;
          const BIGNUM *pub_key;

          DSA_get0_pqg(dsa, &p, &q, &g);
          DSA_get0_key(dsa, &pub_key, NULL);

          print_pubkey_BN(dsa, p, i);
          print_pubkey_BN(dsa, q, i);
          print_pubkey_BN(dsa, g, i);
          print_pubkey_BN(dsa, pub_key, i);
        }
#else
        print_pubkey_BN(dsa, p, i);
        print_pubkey_BN(dsa, q, i);
        print_pubkey_BN(dsa, g, i);
        print_pubkey_BN(dsa, pub_key, i);
#endif
#endif /* !OPENSSL_NO_DSA */
        break;
      }
      case EVP_PKEY_DH:
      {
        DH *dh;
#ifdef HAVE_OPAQUE_EVP_PKEY
        dh = EVP_PKEY_get0_DH(pubkey);
#else
        dh = pubkey->pkey.dh;
#endif
#ifdef HAVE_OPAQUE_RSA_DSA_DH
        {
          const BIGNUM *p;
          const BIGNUM *q;
          const BIGNUM *g;
          const BIGNUM *pub_key;
          DH_get0_pqg(dh, &p, &q, &g);
          DH_get0_key(dh, &pub_key, NULL);
          print_pubkey_BN(dh, p, i);
          print_pubkey_BN(dh, q, i);
          print_pubkey_BN(dh, g, i);
          print_pubkey_BN(dh, pub_key, i);
       }
#else
        print_pubkey_BN(dh, p, i);
        print_pubkey_BN(dh, g, i);
        print_pubkey_BN(dh, pub_key, i);
#endif
        break;
      }
#if 0
      case EVP_PKEY_EC: /* symbol not present in OpenSSL 0.9.6 */
        /* left TODO */
        break;
#endif
      }
      EVP_PKEY_free(pubkey);
    }

    if(psig) {
      for(j = 0; j < psig->length; j++)
        BIO_printf(mem, "%02x:", psig->data[j]);
      push_certinfo("Signature", i);
    }

    PEM_write_bio_X509(mem, x);
    push_certinfo("Cert", i);
  }

  BIO_free(mem);

  return CURLE_OK;
}