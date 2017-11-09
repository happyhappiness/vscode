static int check_hex_digest(const char *hex_digest,
                            const metalink_digest_def *digest_def)
{
  size_t i;
  for(i = 0; hex_digest[i]; ++i) {
    char c = hex_digest[i];
    if(!(('0' <= c && c <= '9') || ('a' <= c && c <= 'z') ||
         ('A' <= c && c <= 'Z'))) {
      return 0;
    }
  }
  return digest_def->dparams->digest_resultlen * 2 == i;
}