(s = publicId; *s; s++) {
    switch (*s) {
    case 0x20:
    case 0xD:
    case 0xA:
      if (p != publicId && p[-1] != 0x20)
        *p++ = 0x20;
      break;
    default:
      *p++ = *s;
    }
  }