        if(p->flags & FLAGS_ALT)
          *fptr++ = '#';

        *fptr = 0;

        if(width >= 0) {
          if(width >= (long)sizeof(work))
            width = sizeof(work)-1;
          /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, "%ld", width);
          fptr += len;
          left -= len;
        }
        if(prec >= 0) {
          /* for each digit in the integer part, we can have one less
             precision */
          size_t maxprec = sizeof(work) - 2;
          double val = p->data.dnum;
          while(val >= 10.0) {
            val /= 10;
            maxprec--;
          }

          if(prec > (long)maxprec)
            prec = maxprec-1;
          /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, ".%ld", prec);
          fptr += len;
        }
        if(p->flags & FLAGS_LONG)
          *fptr++ = 'l';
