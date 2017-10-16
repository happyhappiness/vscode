        if(p->flags & FLAGS_ALT)
          *fptr++ = '#';

        *fptr = 0;

        if(width >= 0) {
          /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, "%ld", width);
          fptr += len;
          left -= len;
        }
        if(prec >= 0) {
          /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, ".%ld", prec);
          fptr += len;
        }
        if(p->flags & FLAGS_LONG)
          *fptr++ = 'l';
