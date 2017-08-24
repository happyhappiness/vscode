{
    unsigned char* oend = output + length;
    while ((oend - optr) >= 3) {
      int len = kwsysBase64_Decode3(ptr, optr);
      optr += len;
      if (len < 3) {
        return (size_t)(optr - output);
      }
      ptr += 4;
    }

    /* Decode the last triplet */

    if (oend - optr == 2) {
      unsigned char temp[3];
      int len = kwsysBase64_Decode3(ptr, temp);
      if (len >= 2) {
        optr[0] = temp[0];
        optr[1] = temp[1];
        optr += 2;
      } else if (len > 0) {
        optr[0] = temp[0];
        optr += 1;
      }
    } else if (oend - optr == 1) {
      unsigned char temp[3];
      int len = kwsysBase64_Decode3(ptr, temp);
      if (len > 0) {
        optr[0] = temp[0];
        optr += 1;
      }
    }
  }