void warnf(struct OperationConfig *config, const char *fmt, ...)
{
  if(!config->global->mute) {
    va_list ap;
    int len;
    char *ptr;
    char print_buffer[256];

    va_start(ap, fmt);
    len = vsnprintf(print_buffer, sizeof(print_buffer), fmt, ap);
    va_end(ap);

    ptr = print_buffer;
    while(len > 0) {
      fputs(WARN_PREFIX, config->global->errors);

      if(len > (int)WARN_TEXTWIDTH) {
        int cut = WARN_TEXTWIDTH-1;

        while(!ISSPACE(ptr[cut]) && cut) {
          cut--;
        }
        if(0 == cut)
          /* not a single cutting position was found, just cut it at the
             max text width then! */
          cut = WARN_TEXTWIDTH-1;

        (void)fwrite(ptr, cut + 1, 1, config->global->errors);
        fputs("\n", config->global->errors);
        ptr += cut+1; /* skip the space too */
        len -= cut;
      }
      else {
        fputs(ptr, config->global->errors);
        len = 0;
      }
    }
  }
}