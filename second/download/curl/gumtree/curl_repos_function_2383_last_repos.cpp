static int
select_next_protocol(unsigned char **out, unsigned char *outlen,
                     const unsigned char *in, unsigned int inlen,
                     const char *key, unsigned int keylen)
{
  unsigned int i;
  for(i = 0; i + keylen <= inlen; i += in[i] + 1) {
    if(memcmp(&in[i + 1], key, keylen) == 0) {
      *out = (unsigned char *) &in[i + 1];
      *outlen = in[i];
      return 0;
    }
  }
  return -1;
}