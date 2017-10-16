   * point returning a value different from sz*nmemb indicates failure.
   */
  const size_t err_rc = (sz * nmemb) ? 0 : 1;

  if(!out->stream) {
    out->bytes = 0; /* nothing written yet */
    if(!out->filename) {
      warnf(config, "Remote filename has no length!\n");
      return err_rc; /* Failure */
    }

    if(config->content_disposition) {
      /* don't overwrite existing files */
      FILE* f = fopen(out->filename, "r");
      if(f) {
        fclose(f);
        warnf(config, "Refusing to overwrite %s: %s\n", out->filename,
              strerror(EEXIST));
        return err_rc; /* Failure */
      }
    }
