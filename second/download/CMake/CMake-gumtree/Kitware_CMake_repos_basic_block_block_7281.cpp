e(beg < end && *beg) {
      beg = Curl_getASN1Element(&lelem, beg, end);
      if(!beg)
        return (const char *) NULL;
    }