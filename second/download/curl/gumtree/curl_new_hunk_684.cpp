
    if(!outs->filename || !*outs->filename) {
      warnf(config, "Remote filename has no length!\n");
      return failure;
    }

    if(outs->is_cd_filename) {
      /* don't overwrite existing files */
      file = fopen(outs->filename, "rb");
      if(file) {
        fclose(file);
        warnf(config, "Refusing to overwrite %s: %s\n", outs->filename,
              strerror(EEXIST));
