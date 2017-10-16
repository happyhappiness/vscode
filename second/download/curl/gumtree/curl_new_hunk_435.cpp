static size_t my_fwrite(void *buffer, size_t sz, size_t nmemb, void *stream)
{
  size_t rc;
  struct OutStruct *out=(struct OutStruct *)stream;
  struct Configurable *config = out->config;

  /*
   * Once that libcurl has called back my_fwrite() the returned value
   * is checked against the amount that was intended to be written, if
   * it does not match then it fails with CURLE_WRITE_ERROR. So at this
   * point returning a value different from sz*nmemb indicates failure.
   */
  const size_t err_rc = (sz * nmemb) ? 0 : 1;

  if(!out->stream) {
    if (!out->filename) {
      warnf(config, "Remote filename has no length!\n");
      return err_rc; /* Failure */
    }

    if (config->content_disposition) {
      /* don't overwrite existing files */
      FILE* f = fopen(out->filename, "r");
      if (f) {
        fclose(f);
        warnf(config, "Refusing to overwrite %s: %s\n", out->filename,
              strerror(EEXIST));
        return err_rc; /* Failure */
      }
    }

    /* open file for writing */
    out->stream=fopen(out->filename, "wb");
    if(!out->stream) {
      warnf(config, "Failed to create the file %s: %s\n", out->filename,
            strerror(errno));
      return err_rc; /* failure */
    }
  }

  rc = fwrite(buffer, sz, nmemb, out->stream);

  if((sz * nmemb) == rc) {
