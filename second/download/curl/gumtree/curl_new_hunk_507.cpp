    if(!out)
      warnf(config, "Failed to open %s to write libcurl code!\n", o);
    else {
      int i;
      const char *c;

      for(i=0; ((c = srchead[i]) != '\0'); i++)
        fprintf(out, "%s\n", c);

      ptr = easycode;
      while(ptr) {
        fprintf(out, "  %s\n", ptr->data);
        ptr = ptr->next;
      }
