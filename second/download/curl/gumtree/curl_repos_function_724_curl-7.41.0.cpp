static int check_hash(const char *filename,
                      const metalink_digest_def *digest_def,
                      const unsigned char *digest, FILE *error)
{
  unsigned char *result;
  digest_context *dctx;
  int check_ok, flags, fd;

  flags = O_RDONLY;
#ifdef O_BINARY
  /* O_BINARY is required in order to avoid binary EOF in text mode */
  flags |= O_BINARY;
#endif

  fd = open(filename, flags);
  if(fd == -1) {
    fprintf(error, "Metalink: validating (%s) [%s] FAILED (%s)\n", filename,
            digest_def->hash_name, strerror(errno));
    return -1;
  }

  dctx = Curl_digest_init(digest_def->dparams);
  if(!dctx) {
    fprintf(error, "Metalink: validating (%s) [%s] FAILED (%s)\n", filename,
            digest_def->hash_name, "failed to initialize hash algorithm");
    close(fd);
    return -2;
  }

  result = malloc(digest_def->dparams->digest_resultlen);
  while(1) {
    unsigned char buf[4096];
    ssize_t len = read(fd, buf, sizeof(buf));
    if(len == 0) {
      break;
    }
    else if(len == -1) {
      fprintf(error, "Metalink: validating (%s) [%s] FAILED (%s)\n", filename,
              digest_def->hash_name, strerror(errno));
      Curl_digest_final(dctx, result);
      close(fd);
      return -1;
    }
    Curl_digest_update(dctx, buf, (unsigned int)len);
  }
  Curl_digest_final(dctx, result);
  check_ok = memcmp(result, digest,
                    digest_def->dparams->digest_resultlen) == 0;
  /* sha*sum style verdict output */
  if(check_ok)
    fprintf(error, "Metalink: validating (%s) [%s] OK\n", filename,
            digest_def->hash_name);
  else
    fprintf(error, "Metalink: validating (%s) [%s] FAILED (digest mismatch)\n",
            filename, digest_def->hash_name);

  free(result);
  close(fd);
  return check_ok;
}