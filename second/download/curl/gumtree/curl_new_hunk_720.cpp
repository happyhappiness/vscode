    if(!out)
      warnf(config, "Failed to open %s to write libcurl code!\n", o);
    else {
      int i;
      const char *c;

      for(i=0; ((c = srchead[i]) != NULL); i++)
        fprintf(out, "%s\n", c);

      /* Declare variables used for complex setopt values */
      for(ptr=easysrc_decl; ptr; ptr = ptr->next)
        fprintf(out, "  %s\n", ptr->data);

