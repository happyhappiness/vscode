{
    if (tp + sizeof(uint16_t) > endp)
      return UV_EINVAL;
    *tp++ = (unsigned char) (val >> 8) & 0xff;
    *tp++ = (unsigned char) val & 0xff;
  }