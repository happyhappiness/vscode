{
      curtok = src;
      if(!saw_xdigit) {
        if(colonp)
          return (0);
        colonp = tp;
        continue;
      }
      if(tp + INT16SZ > endp)
        return (0);
      *tp++ = (unsigned char) ((val >> 8) & 0xff);
      *tp++ = (unsigned char) (val & 0xff);
      saw_xdigit = 0;
      val = 0;
      continue;
    }