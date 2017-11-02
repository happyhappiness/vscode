static void pubkey_show(struct SessionHandle *data,
                        int num,
                        const char *type,
                        const char *name,
                        unsigned char *raw,
                        int len)
{
  size_t left;
  int i;
  char namebuf[32];
  char *buffer;

  left = len*3 + 1;
  buffer = malloc(left);
  if(buffer) {
    char *ptr=buffer;
    snprintf(namebuf, sizeof(namebuf), "%s(%s)", type, name);
    for(i=0; i< len; i++) {
      snprintf(ptr, left, "%02x:", raw[i]);
      ptr += 3;
      left -= 3;
    }
    infof(data, "   %s: %s\n", namebuf, buffer);
    Curl_ssl_push_certinfo(data, num, namebuf, buffer);
    free(buffer);
  }
}