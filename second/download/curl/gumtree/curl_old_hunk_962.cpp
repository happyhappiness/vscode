  char *o = config->libcurl;

  if(o) {
    FILE *out;
    bool fopened = FALSE;
    if(strcmp(o, "-")) {
      out = fopen(o, "w");
      fopened = TRUE;
    }
    else
      out = stdout;
    if(!out)
      warnf(config, "Failed to open %s to write libcurl code!\n", o);
