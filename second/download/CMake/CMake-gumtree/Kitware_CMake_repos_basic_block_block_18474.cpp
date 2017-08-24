{
      curtok = src;
      if (!seen_xdigits) {
        if (colonp)
          return UV_EINVAL;
        colonp = tp;
        continue;
      } else if (*src == '\0') {
        return UV_EINVAL;
      }
      if (tp + sizeof(uint16_t) > endp)
        return UV_EINVAL;
      *tp++ = (unsigned char) (val >> 8) & 0xff;
      *tp++ = (unsigned char) val & 0xff;
      seen_xdigits = 0;
      val = 0;
      continue;
    }