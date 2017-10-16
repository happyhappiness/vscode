      out = fopen(o, "w");
      fopened = TRUE;
    }
    else
      out = stdout;
    if(!out)
      warnf(config, "Failed to open %s to write libcurl code!\n", o);
    else {
      int i;
      const char *c;

      for(i=0; ((c = srchead[i]) != NULL); i++)
        fprintf(out, "%s\n", c);
