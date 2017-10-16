        if(p->flags & FLAGS_PREC)
          prec = p->precision;
        else if(p->flags & FLAGS_PRECPARAM)
          prec = (long)vto[p->precision].data.num.as_signed;

        if(p->flags & FLAGS_LEFT)
          strcat(formatbuf, "-");
        if(p->flags & FLAGS_SHOWSIGN)
          strcat(formatbuf, "+");
        if(p->flags & FLAGS_SPACE)
          strcat(formatbuf, " ");
        if(p->flags & FLAGS_ALT)
          strcat(formatbuf, "#");

        fptr=&formatbuf[strlen(formatbuf)];

        if(width >= 0) {
          /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, "%ld", width);
          fptr += len;
          left -= len;
