{
    if(Curl_raw_toupper(*first) != Curl_raw_toupper(*second)) {
      break;
    }
    max--;
    first++;
    second++;
  }