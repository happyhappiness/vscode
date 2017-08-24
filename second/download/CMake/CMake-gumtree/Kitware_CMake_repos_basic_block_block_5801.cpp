f(src->set.postfieldsize && src->set.str[i]) {
    /* postfieldsize is curl_off_t, Curl_memdup() takes a size_t ... */
    dst->set.str[i] = Curl_memdup(src->set.str[i],
                                  curlx_sotouz(src->set.postfieldsize));
    if(!dst->set.str[i])
      return CURLE_OUT_OF_MEMORY;
    /* point to the new copy */
    dst->set.postfields = dst->set.str[i];
  }