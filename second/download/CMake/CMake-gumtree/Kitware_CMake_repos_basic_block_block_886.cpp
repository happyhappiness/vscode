{
      unsigned char temp[3];
      int len = kwsysBase64_Decode3(ptr, temp);
      if (len > 0) {
        optr[0] = temp[0];
        optr += 1;
      }
    }