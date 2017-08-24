f(*f != '%') {
      /* This isn't a format spec, so write everything out until the next one
         OR end of string is reached.  */
      do {
        OUTCHAR(*f);
      } while(*++f && ('%' != *f));
      continue;
    }