     va_list ap;
     int len;
     char *ptr;
     char print_buffer[256];
 
     va_start(ap, fmt);
-    va_start(ap, fmt);
     len = vsnprintf(print_buffer, sizeof(print_buffer), fmt, ap);
     va_end(ap);
 
     ptr = print_buffer;
     while(len > 0) {
       fputs(WARN_PREFIX, config->errors);
