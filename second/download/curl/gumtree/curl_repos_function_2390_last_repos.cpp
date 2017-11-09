static void pubkey_show(struct Curl_easy *data,
                        BIO *mem,
                        int num,
                        const char *type,
                        const char *name,
#ifdef HAVE_OPAQUE_RSA_DSA_DH
                        const
#endif
                        BIGNUM *bn)
{
  char *ptr;
  char namebuf[32];

  snprintf(namebuf, sizeof(namebuf), "%s(%s)", type, name);

  if(bn)
    BN_print(mem, bn);
  push_certinfo(namebuf, num);
}