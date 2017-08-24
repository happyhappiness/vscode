{
    Curl_getASN1Element(&cert->version, elem.beg, elem.end);
    beg = Curl_getASN1Element(&elem, beg, end);
  }