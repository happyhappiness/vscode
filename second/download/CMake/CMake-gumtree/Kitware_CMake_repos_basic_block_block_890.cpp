{
      int len = kwsysBase64_Decode3(ptr, optr);
      optr += len;
      if (len < 3) {
        return (size_t)(optr - output);
      }
      ptr += 4;
    }