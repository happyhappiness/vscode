{
    cert->issuerUniqueID = elem;
    if(beg < end)
      beg = Curl_getASN1Element(&elem, beg, end);
  }