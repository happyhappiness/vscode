        if(p->flags & FLAGS_PREC)
          prec = p->precision;
        else if(p->flags & FLAGS_PRECPARAM)
          prec = (long)vto[p->precision].data.num.as_signed;

        if(p->flags & FLAGS_LEFT)
          *fptr++ = '-';
        if(p->flags & FLAGS_SHOWSIGN)
          *fptr++ = '+';
        if(p->flags & FLAGS_SPACE)
          *fptr++ = ' ';
        if(p->flags & FLAGS_ALT)
          *fptr++ = '#';

        *fptr = 0;

        if(width >= 0) {
          /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, "%ld", width);
          fptr += len;
          left -= len;
